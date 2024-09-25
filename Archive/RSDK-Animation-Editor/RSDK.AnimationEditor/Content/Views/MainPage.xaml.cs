using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Controls.Primitives;
using Microsoft.UI.Xaml.Media;
using Microsoft.UI.Xaml.Media.Animation;
using RSDK.AnimationEditor.Content.ViewModels;
using RSDK.AnimationEditor.Content.Views.Other;
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

namespace RSDK.AnimationEditor.Content.Views
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {

        public MainViewModel ViewModel => (MainViewModel)DataContext;
        public static Grid MDragRegion { get; set; }
        ApplicationDataContainer localSettings = ApplicationData.Current.LocalSettings;
        public MainPage()
        {
            InitializeComponent();
            DataContext = new MainViewModel();

            String tabs = localSettings.Values["isTabsEnabled"] as string;
            if (tabs != "yep")
            {
                FindName("AppTitleBar");
                MainWindow.XamlWindow.Activated += _Activated;
            }
            SetupRecentFiles();
        }

        private async Task SetupRecentFiles()
        {
            foreach (AccessListEntry entry in StorageApplicationPermissions.MostRecentlyUsedList.Entries)
            {
                var file = await StorageApplicationPermissions.MostRecentlyUsedList.GetFileAsync(entry.Token);
                var menuflyoutitem = new MenuFlyoutItem();
                menuflyoutitem.Icon = new SymbolIcon(Symbol.Document);
                menuflyoutitem.Text = $"{file.Name} - {(file.FileType == ".ani" ? "RSDKv4" : file.FileType == ".bin" ? "RSDKv5" : "Unknown")}";
                menuflyoutitem.Click +=
                async (sender, args) =>
                {
                    try
                    {
                        await ViewModel.FileOpen(file.Path);
                        String tabs = localSettings.Values["isTabsEnabled"] as string;
                        if (tabs == "yep")
                        {
                            // Disable tabs to prevent the user from switching tabs while opening a file, this will ruin the icon/header
                            TabbedWindow.tabs.IsEnabled = false;

                            var iconSource = new Microsoft.UI.Xaml.Controls.ImageIconSource();
                            iconSource.ImageSource = ViewModel.IsHitboxV5 ? new Microsoft.UI.Xaml.Media.Imaging.BitmapImage(new Uri("ms-appx:///Content/Resources/Icons/RSDKv5.ico")) : new Microsoft.UI.Xaml.Media.Imaging.BitmapImage(new Uri("ms-appx:///Content/Resources/Icons/RSDKv4.ico"));

                            (TabbedWindow.tabs.TabItems[TabbedWindow.tabs.SelectedIndex] as TabViewItem).IconSource = iconSource;
                            (TabbedWindow.tabs.TabItems[TabbedWindow.tabs.SelectedIndex] as TabViewItem).Header = $"{file.Name} - {ViewModel.AnimationData.VersionString}";

                            TabbedWindow.tabs.IsEnabled = true;
                        }
                        else
                        {
                            WindowHelper.GetWindowForElement(this).Title = file.Name;
                        }

                        string[] columnNames = { "Column0", "Column1", "Column2" };
                        foreach (string name in columnNames)
                        {
                            FindName(name);
                        }

                    }
                    catch (Exception ex)
                    {
                        ContentDialog Dialog = new ContentDialog
                        {
                            XamlRoot = XamlRoot,
                            Style = Application.Current.Resources["DefaultContentDialogStyle"] as Style,
                            Title = "Something went wrong",
                            Content = $"There was a problem loading \"{file.Name}\". {ex.Message}",
                            PrimaryButtonText = "Close"
                        };
                        var result = await Dialog.ShowAsync();
                        if (result == ContentDialogResult.Primary)
                        {
                            OpenFromDialog();
                        }

                    };
                };

                RecentSubmenu.Items.Insert(RecentSubmenu.Items.Count - 2, menuflyoutitem);
            }

            RecentClear.Click +=
            async (sender, args) =>
            {
                StorageApplicationPermissions.MostRecentlyUsedList.Clear();
            };
        }

        private void _Activated(object sender, WindowActivatedEventArgs args)
        {
            if (args.WindowActivationState == WindowActivationState.Deactivated)
            {
                AppTitleTextBlock.Foreground =
                    (SolidColorBrush)App.Current.Resources["WindowCaptionForegroundDisabled"];
            }
            else
            {
                AppTitleTextBlock.Foreground =
                    (SolidColorBrush)App.Current.Resources["WindowCaptionForeground"];
            }
        }

        #region Menubar

        private async void FileOpen_Click(object sender, RoutedEventArgs e)
        {
            var Picker = new FileOpenPicker();

            Picker.FileTypeFilter.Add(".ani");
            Picker.FileTypeFilter.Add(".bin");

            var window = WindowHelper.GetWindowForElement(this);
            var hwnd = WindowNative.GetWindowHandle(window);

            InitializeWithWindow.Initialize(Picker, hwnd);

            StorageFile File = await Picker.PickSingleFileAsync();

            if (File != null)
            {
                try
                {
                    await ViewModel.FileOpen(File.Path);
                    StorageApplicationPermissions.MostRecentlyUsedList.Add(File);

                    String tabs = localSettings.Values["isTabsEnabled"] as string;
                    if (tabs == "yep")
                    {
                        // Disable tabs to prevent the user from switching tabs while opening a file, this will ruin the icon/header
                        TabbedWindow.tabs.IsEnabled = false;

                        var iconSource = new Microsoft.UI.Xaml.Controls.ImageIconSource();
                        iconSource.ImageSource = ViewModel.IsHitboxV5 ? new Microsoft.UI.Xaml.Media.Imaging.BitmapImage(new Uri("ms-appx:///Content/Resources/Icons/RSDKv5.ico")) : new Microsoft.UI.Xaml.Media.Imaging.BitmapImage(new Uri("ms-appx:///Content/Resources/Icons/RSDKv4.ico"));

                        (TabbedWindow.tabs.TabItems[TabbedWindow.tabs.SelectedIndex] as TabViewItem).IconSource = iconSource;
                        (TabbedWindow.tabs.TabItems[TabbedWindow.tabs.SelectedIndex] as TabViewItem).Header = $"{File.Name} - {ViewModel.AnimationData.VersionString}";

                        TabbedWindow.tabs.IsEnabled = true;
                    }
                    else
                    {
                        WindowHelper.GetWindowForElement(this).Title = File.Name;
                    }

                    string[] columnNames = { "Column0", "Column1", "Column2" };
                    foreach (string name in columnNames)
                    {
                        FindName(name);
                    }
                }
                catch (Exception ex)
                {
                    ContentDialog Dialog = new ContentDialog
                    {
                        XamlRoot = XamlRoot,
                        Style = Application.Current.Resources["DefaultContentDialogStyle"] as Style,
                        Title = "Something went wrong",
                        Content = $"There was a problem loading \"{File.Name}\". {ex.Message}",
                        PrimaryButtonText = "Close"
                    };
                    var result = await Dialog.ShowAsync();
                    if (result == ContentDialogResult.Primary)
                    {
                        OpenFromDialog();
                    }
                };
            }
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
        private async void ViewHitbox_Click(object sender, RoutedEventArgs e)
        {
            if (ViewModel.isHitboxVX)
            {
                new HitboxManagerVX(ViewModel).Activate();
            }
            else if (ViewModel.IsHitboxV5)
            {
                //new HitboxManagerV5(ViewModel).Activate();
                var dialog = new HitboxManagerV5(ViewModel);
                dialog.XamlRoot = this.XamlRoot;

                var result = await dialog.ShowAsync();
                if (result == ContentDialogResult.Primary)
                {

                }

            }
        }

        private void ViewTexture_Click(object sender, RoutedEventArgs e)
        {
            if (ViewModel.IsAnimationDataLoaded)
            {
                var basePath = Path.Combine(Path.GetDirectoryName(ViewModel.FileName), ViewModel.PathMod);
                new TextureManager(ViewModel, basePath).Activate();
            }
        }

        private void Col2FrameView(object sender, RoutedEventArgs e) { Column2Frame.Navigate((bool)ViewMode.IsChecked ? typeof(HitboxContent) : typeof(SpritePropertiesContent), null, new SuppressNavigationTransitionInfo()); }

        private void Settings_Click(object sender, RoutedEventArgs e)
        {
            String tabs = localSettings.Values["isTabsEnabled"] as string;
            if (tabs == "yep")
            {
                var settings = new TabViewItem();
                settings.IconSource = new SymbolIconSource() { Symbol = Symbol.Setting };
                settings.Header = "Settings";
                settings.Content = new Settings();
                TabbedWindow.tabs.TabItems.Add(settings);
                TabbedWindow.tabs.SelectedItem = settings;
            }
            else
            {
                if (Frame.CanGoForward)
                {
                    Frame.GoForward();
                }
                else
                {
                    Frame.Navigate(typeof(Settings));
                }
            }
        }

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
            //var fd = Xe.Tools.Wpf.Dialogs.FileDialog.Factory(this,
            //    Xe.Tools.Wpf.Dialogs.FileDialog.Behavior.Open,
            //    Xe.Tools.Wpf.Dialogs.FileDialog.Type.Any, false);
            //if (fd.ShowDialog() == true)
            //{
            //    ViewModel.FileOpen(fd.FileName);
            //}

            FileOpenPicker Picker = new();
            Picker.FileTypeFilter.Add(".ani");
            Picker.FileTypeFilter.Add(".bin");
            var window = WindowHelper.GetWindowForElement(this);
            var hwnd = WindowNative.GetWindowHandle(window);
            InitializeWithWindow.Initialize(Picker, hwnd);
            Windows.Storage.StorageFile File = await Picker.PickSingleFileAsync();
            if (File != null)
            {
                try
                {
                    //Load file
                    await ViewModel.FileOpen(File.Path);
                }
                catch (Exception ex)
                {
                    ContentDialog Dialog = new ContentDialog();

                    Dialog.XamlRoot = XamlRoot;
                    Dialog.Style = Application.Current.Resources["DefaultContentDialogStyle"] as Style;
                    Dialog.Title = "Something went wrong";
                    Dialog.Content = $"There was a problem loading \"{File.Name}\". {ex.Message}";
                    Dialog.PrimaryButtonText = "Close";
                    var result = await Dialog.ShowAsync();
                    if (result == ContentDialogResult.Primary)
                    {
                        OpenFromDialog();
                    }
                };
            }
            else
            {
                try
                {
                    /*
                    Incase the user clicks cancel
                    on the file dialog, wait for
                    them to open a file
                    */
                    await ViewModel.FileOpen(File.Path);
                }
                catch (Exception ex)
                {
                    ContentDialog Dialog = new ContentDialog();

                    Dialog.XamlRoot = XamlRoot;
                    Dialog.Style = Application.Current.Resources["DefaultContentDialogStyle"] as Style;
                    Dialog.Title = "Something went wrong";
                    Dialog.Content = $"There was a problem loading \"{File.Name}\". {ex.Message}";
                    Dialog.PrimaryButtonText = "Close";
                    var result = await Dialog.ShowAsync();
                    if (result == ContentDialogResult.Primary)
                    {
                        OpenFromDialog();
                    }
                };
            }
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
            //List<UIElement> itemsToRemove = new List<UIElement>();
            foreach (UIElement element in CanvasControlStack.Children)
            {
                CanvasControlStack.Children.Remove(element);
                overflowContentHost.Children.Add(element);
            }


            /*
            double totalWidth = 0;
            foreach (UIElement element in CanvasControlStack.Children)
            {
                totalWidth += element.DesiredSize.Width;
            }

            if (totalWidth > CanvasControlStack.ActualWidth)
            {
                // Move controls that don't fit into overflow menu
                overflowMenu.IsOpen = true;
                overflowPanel.Children.Clear();

                List<UIElement> itemsToRemove = new List<UIElement>();
                foreach (UIElement element in CanvasControlStack.Children)
                {
                    if (totalWidth > CanvasControlStack.ActualWidth)
                    {
                        itemsToRemove.Add(element);
                        overflowPanel.Children.Add(element);
                        totalWidth -= element.DesiredSize.Width;
                    }
                    else
                    {
                        break;
                    }
                }
                // Remove the items from CanvasControlStack.Children
                foreach (UIElement element in itemsToRemove)
                {
                    CanvasControlStack.Children.Remove(element);
                }
            }
            else
            {
                // Move controls back to stack panel
                overflowMenu.IsOpen = false;
                foreach (UIElement element in overflowPanel.Children)
                {
                    overflowPanel.Children.Remove(element);
                    CanvasControlStack.Children.Add(element);
                }
            }
            */
        }



    }
}