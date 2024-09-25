using Microsoft.UI;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Controls.Primitives;
using Microsoft.UI.Xaml.Media;
using Microsoft.UI.Xaml.Media.Animation;
using RSDK.AnimationEditor.Experimental.Content.ViewModels;
using RSDK.AnimationEditor.Experimental.Content.Views.Other;
using System;
using System.Collections.Generic;
using System.IO;
using System.Threading.Tasks;
using Windows.Foundation;
using Windows.Storage;
using Windows.Storage.AccessCache;
using Windows.Storage.Pickers;
using WinRT.Interop;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace RSDK.AnimationEditor.Experimental.Content.Views
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainViewModel ViewModel => (MainViewModel)(MainWindow.tabs.TabItems[MainWindow.tabs.SelectedIndex] as TabViewItem).DataContext;
        public static Grid MDragRegion { get; set; }
        public Button settingsbutton { get; set; }
        ApplicationDataContainer localSettings = ApplicationData.Current.LocalSettings;
        public MainPage()
        {
            InitializeComponent();
            SetupRecentFiles();

            settingsbutton = SettingsButton;

            ThemeHelper.Initialize();
            RequestedTheme = ThemeHelper.RootTheme;
        }

        private async Task SetupRecentFiles()
        {
            foreach (AccessListEntry entry in StorageApplicationPermissions.MostRecentlyUsedList.Entries)
            {
                var file = await StorageApplicationPermissions.MostRecentlyUsedList.GetFileAsync(entry.Token);
                var menuflyoutitem = new MenuFlyoutItem();
                menuflyoutitem.Icon = new SymbolIcon(Symbol.Document);
                menuflyoutitem.Text = $"{file.Name} - {(file.FileType == ".ani" ? "RSDKv4" : file.FileType == ".bin" ? "RSDKv5" : "Unknown")}";
                menuflyoutitem.Click += async (sender, args) => { await Open(false, file); };

                RecentSubmenu.Items.Insert(RecentSubmenu.Items.Count - 2, menuflyoutitem);
            }

            RecentClear.Click +=
            (sender, args) =>
            {
                StorageApplicationPermissions.MostRecentlyUsedList.Clear();
            };
        }

        private async Task Open(bool showDialog, StorageFile file = null)
        {
            StorageFile selectedFile = file;
            if (showDialog)
            {
                var picker = new FileOpenPicker();
                picker.FileTypeFilter.Add(".ani");
                picker.FileTypeFilter.Add(".bin");
                var window = WindowHelper.GetWindowForElement(this);
                var hwnd = WindowNative.GetWindowHandle(window);
                InitializeWithWindow.Initialize(picker, hwnd);
                selectedFile = await picker.PickSingleFileAsync();
            }
            if (selectedFile != null)
            {
                try
                {
                    await ViewModel.FileOpen(selectedFile.Path);
                    StorageApplicationPermissions.MostRecentlyUsedList.Add(selectedFile);
                    (MainWindow.tabs.TabItems[MainWindow.tabs.SelectedIndex] as TabViewItem).IconSource = new SymbolIconSource() { Symbol = Symbol.Document };
                }
                catch (Exception ex)
                {
                    ContentDialog Dialog = new ContentDialog
                    {
                        XamlRoot = XamlRoot,
                        Style = Application.Current.Resources["DefaultContentDialogStyle"] as Style,
                        Title = "Something went wrong",
                        Content = $"There was a problem loading \"{selectedFile.Name}\". {ex.Message}",
                        PrimaryButtonText = "Close"
                    };
                    var result = await Dialog.ShowAsync();
                    if (result == ContentDialogResult.Primary)
                    {
                        await Open(true);
                    }
                }
            }
        }

        #region Menubar

        private async void FileOpen_Click(object sender, RoutedEventArgs e)
        {
            await Open(true);
        }

        private void FileSave_Click(object sender, RoutedEventArgs e)
        {
            ViewModel.FileSave();
        }

        private async void FileSaveAs_Click(object sender, RoutedEventArgs e)
        {
            var Picker = new Windows.Storage.Pickers.FileSavePicker();

            var window = WindowHelper.GetWindowForElement(this);
            var hwnd = WindowNative.GetWindowHandle(window);

            InitializeWithWindow.Initialize(Picker, hwnd);

            StorageFile file = await Picker.PickSaveFileAsync();
            if (file != null)
            {
                CachedFileManager.DeferUpdates(file);
                ViewModel.FileSave(file.Name);
            }
        }

        private void FileExit_Click(object sender, RoutedEventArgs e)
        {
            WindowHelper.GetWindowForElement(this).Close();
        }

        private void ViewHome_Click(object sender, RoutedEventArgs e)
        {
            var window = new Window();
            window.Activate();
            window.Content = new Home();
            WindowHelper.TrackWindow(window);

            window.AppWindow.TitleBar.ExtendsContentIntoTitleBar = true;
            window.AppWindow.TitleBar.ButtonBackgroundColor = Colors.Transparent;
            window.AppWindow.TitleBar.ButtonInactiveBackgroundColor = Colors.Transparent;

            window.SystemBackdrop = new MicaBackdrop();
        }

        private async void ViewHitbox_Click(object sender, RoutedEventArgs e)
        {
            if (ViewModel.isHitboxVX)
            {
                var window = new HitboxEditorVX(ViewModel);
                WindowHelper.TrackWindow(window);
                window.Activate();
            }
            else if (ViewModel.IsHitboxV5)
            {
                var editor = new HitboxEditorV5(ViewModel);
                var flyout = new Flyout();
                flyout.Content = editor;

                FlyoutShowOptions options = new FlyoutShowOptions();
                options.ShowMode = FlyoutShowMode.Standard;

                flyout.ShowAt(ViewMenuItem, options);
            }
        }

        private void ViewTexture_Click(object sender, RoutedEventArgs e)
        {
            if (ViewModel.IsAnimationDataLoaded)
            {
                var basePath = Path.Combine(Path.GetDirectoryName(ViewModel.FileName), ViewModel.PathMod);
                var window = new TextureLibrary(ViewModel, basePath);
                WindowHelper.TrackWindow(window);
                window.Activate();
            }
        }

        private void Col2FrameView(object sender, RoutedEventArgs e) { Column2Frame.Navigate((bool)ViewMode.IsChecked ? typeof(HitboxContent) : typeof(SpritePropertiesContent), null, new SuppressNavigationTransitionInfo()); }

        #endregion

        #region Column 2

        private void Column2Frame_Loaded(object sender, RoutedEventArgs e)
        {
            if (Column2Frame.Content == null)
            {
                Column2Frame.Navigate(typeof(SpritePropertiesContent));
            }
        }

        #endregion

        #region Misc

        private async void OpenFromDialog()
        {
            Open(true);
        }

        #endregion

        private void AnimList_RightTapped(object sender, Microsoft.UI.Xaml.Input.RightTappedRoutedEventArgs e)
        {
            var flyout = FlyoutBase.GetAttachedFlyout((FrameworkElement)sender);
            var options = new FlyoutShowOptions()
            {
                Position = e.GetPosition((FrameworkElement)sender),
                ShowMode = FlyoutShowMode.Standard,
                Placement = FlyoutPlacementMode.BottomEdgeAlignedLeft
            };

            //AnimationListContextMenu.ShowAt((FrameworkElement)sender, options);
        }

        private async void Rename_Click(object sender, RoutedEventArgs e)
        {
            RenameDialog Dialog = new();

            Dialog.XamlRoot = XamlRoot;
            var result = await Dialog.ShowAsync();
            if (result == ContentDialogResult.Primary)
            {
            }
        }
        private void CanvasControlStack_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            double availableWidth = controlColumn.ActualWidth;
            List<UIElement> overflowElements = new List<UIElement>();
            double totalWidth = 0;

            Grid mainGrid = (Grid)sender; // Get the main Grid containing CanvasControlGrid

            foreach (UIElement element in CanvasControlGrid.Children)
            {
                if (element is Button button && Grid.GetColumn(button) != 0)
                {
                    element.Measure(new Size(double.PositiveInfinity, double.PositiveInfinity));
                    double elementWidth = element.DesiredSize.Width;
                    totalWidth += elementWidth;

                    if (totalWidth > availableWidth - 100)
                    {
                        overflowElements.Add(element);
                        totalWidth -= elementWidth;
                        Canvas.SetZIndex(element, -1);
                    }
                    else
                    {
                        Canvas.SetZIndex(element, 0);
                    }
                }
            }

            SeparatorOverflow.Visibility = ButtonOverflow.Visibility = (overflowElements.Count > 0) ? Visibility.Visible : Visibility.Collapsed;

            OverflowItemsPanel.Children.Clear();

            foreach (UIElement element in overflowElements)
            {
                CanvasControlGrid.Children.Remove(element);
                OverflowItemsPanel.Children.Add(element);
            }

            for (int i = OverflowItemsPanel.Children.Count - 1; i >= 0; i--)
            {
                UIElement element = OverflowItemsPanel.Children[i];
                double elementWidth = element.DesiredSize.Width;
                totalWidth += elementWidth;

                if (totalWidth <= availableWidth + 100)
                {
                    OverflowItemsPanel.Children.RemoveAt(i);
                    CanvasControlGrid.Children.Add(element);
                    Canvas.SetZIndex(element, 0);
                }
                else
                {
                    OverflowItemsPanel.Children.Insert(i, element);
                    break;
                }
            }
        }


        private async void Canvas_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            ViewModel.ViewWidth = e.NewSize.Width;
            ViewModel.ViewHeight = e.NewSize.Height;
        }

        private void Canvas_PointerWheelChanged(object sender, Microsoft.UI.Xaml.Input.PointerRoutedEventArgs e)
        {
            ViewModel.Zoom += (e.GetCurrentPoint(canvas).Properties.MouseWheelDelta / 120) * 0.40;
        }

        private void ButtonZoomIn_Click(object sender, RoutedEventArgs e)
        {
            ViewModel.Zoom += 1;
        }

        private void ButtonZoomOut_Click(object sender, RoutedEventArgs e)
        {
            ViewModel.Zoom -= 1;
        }

        private void RestoreDefaultZoom(object sender, RoutedEventArgs e)
        {
            ViewModel.Zoom = 3;
        }

        private async void FileNew_Click(object sender, RoutedEventArgs e)
        {
            var dialog = new NewFileDialog();
            dialog.XamlRoot = this.XamlRoot;


            var result = await dialog.ShowAsync();

        }
    }
}