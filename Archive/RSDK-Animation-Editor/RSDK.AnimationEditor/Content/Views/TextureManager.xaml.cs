using Microsoft.UI;
using Microsoft.UI.Windowing;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Media;
using RSDK.AnimationEditor.Content.ViewModels;
using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using Windows.Graphics;
using Windows.Storage.Pickers;
using WinRT.Interop;
using WinUIEx;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace RSDK.AnimationEditor.Content.Views
{
    /// <summary>
    /// An empty window that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class TextureManager : WinUIEx.WindowEx
    {
        public string BasePath { get; private set; }
        public TextureWindowViewModel ViewModel => rootGrid.DataContext as TextureWindowViewModel;
        public MainViewModel MainViewModel { get; }
        public int SelectedIndex
        {
            get => ViewModel.SelectedIndex;
            set => ViewModel.SelectedIndex = value;
        }

        public TextureManager(MainViewModel mainViewModel)
        {
            InitializeComponent();
            MainViewModel = mainViewModel;
            rootGrid.DataContext = new TextureWindowViewModel(mainViewModel, BasePath);
        }

        public TextureManager(MainViewModel mainViewModel, string basePath)
        {
            InitializeComponent();
            //SystemBackdrop = new MicaBackdrop();

            BasePath = basePath;
            MainViewModel = mainViewModel;

            rootGrid.DataContext = new TextureWindowViewModel(mainViewModel, BasePath);

            //AppWindow.TitleBar.ExtendsContentIntoTitleBar = true;
            //AppWindow.TitleBar.ButtonBackgroundColor = Colors.Transparent;
            //AppWindow.TitleBar.ButtonInactiveBackgroundColor = Colors.Transparent;

            var LeftInset = CompactFlyoutButton.Width + 8 / GetScaleAdjustment();
            var RightInset = AppWindow.TitleBar.RightInset / GetScaleAdjustment();

            wDragRect.Margin = new Thickness(LeftInset, 0, RightInset, 0);

            ExtendsContentIntoTitleBar = true;

            this.CenterOnScreen();
        }


        #region Functionality

        private AppWindow GetAppWindowForCurrentWindow()
        {
            return AppWindow.GetFromWindowId(Win32Interop.GetWindowIdFromWindow(WindowNative.GetWindowHandle(this)));
        }
        private async void Add_Click(object sender, RoutedEventArgs e)
        {

            /*
            var dialog = FileDialog.Factory(this, FileDialog.Behavior.Open, FileDialog.Type.ImageGif);
            if (dialog.ShowDialog() == true)
            {
            var fileName = AddTextureToDirectory(dialog.FileName);
               if (fileName != null)
                {
                    ViewModel.AddTexture(fileName);
                    SelectedIndex = ViewModel.Count - 1;
                }
            }
            */



            FileOpenPicker Picker = new();
            Picker.ViewMode = PickerViewMode.Thumbnail;
            Picker.FileTypeFilter.Add(".gif");
            IntPtr hwnd = WindowNative.GetWindowHandle(this);
            InitializeWithWindow.Initialize(Picker, hwnd);
            Windows.Storage.StorageFile File = await Picker.PickSingleFileAsync();
            if (File != null)
            {
                try
                {
                    ViewModel.AddTexture(Path.Combine(File.Path));
                    SelectedIndex = ViewModel.Count - 1;
                }
                catch (Exception)
                {
                    //Dialog
                }
            }
            else
            {
                //No file selected, do nothing
            }







        }

        //Original removal code
        /*const string message = "Do you want to delete the file? If you click No, it will be deleted only from this application.";

         var index = SelectedIndex;
         switch (MessageBox.Show(message, "Delete confirmation", MessageBoxButton.YesNoCancel, MessageBoxImage.Warning))
         {
             case MessageBoxResult.Yes:
                 ViewModel.RemoveTexture(SelectedIndex, true);
                 break;
             case MessageBoxResult.No:
                 ViewModel.RemoveTexture(SelectedIndex, false);
                 break;
             default:
                 // Do nothing.
                 index = -1;
                 break;
         }
         if (index >= 0)
         {
             if (index >= ViewModel.Count)
                 index--;
             SelectedIndex = index;
         }*/

        private async void Remove_Click(object sender, RoutedEventArgs e)
        {
            ContentDialog Dialog = new ContentDialog();
            Dialog.XamlRoot = Content.XamlRoot;
            Dialog.Style = Application.Current.Resources["DefaultContentDialogStyle"] as Style;
            Dialog.Title = "Remove file?";
            Dialog.Content = $"Do you want to remove {ViewModel.SelectedValue} from file.ani?";
            Dialog.PrimaryButtonText = "Remove";
            Dialog.CloseButtonText = "Cancel";
            var result = await Dialog.ShowAsync();
            if (result == ContentDialogResult.Primary)
            {
                ViewModel.RemoveTexture(SelectedIndex, false);
            }
        }

        private async void Delete_Click(object sender, RoutedEventArgs e)
        {
            ContentDialog Dialog = new ContentDialog();
            Dialog.XamlRoot = Content.XamlRoot;
            Dialog.Style = Application.Current.Resources["DefaultContentDialogStyle"] as Style;
            Dialog.Title = "Delete file permanently?";
            Dialog.Content = $"If you delete {ViewModel.SelectedValue}, you won't be able to recover it. Do you want to delete it?";
            Dialog.PrimaryButtonText = "Delete";
            Dialog.CloseButtonText = "Cancel";
            var result = await Dialog.ShowAsync();
            if (result == ContentDialogResult.Primary)
            {
                ViewModel.RemoveTexture(SelectedIndex, true);
            }
        }

        #endregion

        private void window_SizeChanged(object sender, SizeChangedEventArgs e)
        {

            // If the TitleBar's height is tall, that means we're coming from the
            // compact state. This will set the TitleBar's height to standard, so
            // the code shouldn't run again
            // This is most likely inefficient but it's all that I have right now :)

            if (WindowTitleHost.Visibility == Visibility.Collapsed && rootGrid.ActualWidth >= 650)
            {
                WindowTitleHost.Visibility = Visibility.Visible;
                ListHost.Visibility = Visibility.Visible;
                CompactModeTitleBar.Visibility = Visibility.Collapsed;

                imgHost.BorderThickness = new Thickness(1, 1, 0, 0);
                imgHost.CornerRadius = new CornerRadius(8, 0, 0, 0);
                Grid.SetColumn(imgHost, 1);
                Grid.SetColumnSpan(imgHost, 1);

            }
            if (WindowTitleHost.Visibility == Visibility.Visible && rootGrid.ActualWidth <= 650)
            {
                WindowTitleHost.Visibility = Visibility.Collapsed;
                ListHost.Visibility = Visibility.Collapsed;
                CompactModeTitleBar.Visibility = Visibility.Visible;

                imgHost.BorderThickness = new Thickness(0, 1, 0, 0);
                imgHost.CornerRadius = new CornerRadius(0, 0, 0, 0);
                Grid.SetColumn(imgHost, 0);
                Grid.SetColumnSpan(imgHost, 2);
            }
        }

        [DllImport("Shcore.dll", SetLastError = true)]
        internal static extern int GetDpiForMonitor(IntPtr hmonitor, Monitor_DPI_Type dpiType, out uint dpiX, out uint dpiY);

        internal enum Monitor_DPI_Type : int
        {
            MDT_Effective_DPI = 0,
            MDT_Angular_DPI = 1,
            MDT_Raw_DPI = 2,
            MDT_Default = MDT_Effective_DPI
        }

        private double GetScaleAdjustment()
        {
            IntPtr hWnd = WindowNative.GetWindowHandle(this);
            WindowId wndId = Win32Interop.GetWindowIdFromWindow(hWnd);
            DisplayArea displayArea = DisplayArea.GetFromWindowId(wndId, DisplayAreaFallback.Primary);
            IntPtr hMonitor = Win32Interop.GetMonitorFromDisplayId(displayArea.DisplayId);

            // Get DPI.
            int result = GetDpiForMonitor(hMonitor, Monitor_DPI_Type.MDT_Default, out uint dpiX, out uint _);
            if (result != 0)
            {
                throw new Exception("Could not get DPI for monitor.");
            }

            uint scaleFactorPercent = (uint)(((long)dpiX * 100 + (96 >> 1)) / 96);
            return scaleFactorPercent / 100.0;
        }

        private async void wDragRect_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            int x = AppWindow.Size.Width - (int)wDragRect.ActualWidth - (int)e.NewSize.Width - 16;
            int y = 0;
            int width = (int)e.NewSize.Width;
            int height = (int)e.NewSize.Height;
            var dragrects = new RectInt32[] { new RectInt32(x, y, width, height) };
            AppWindow.TitleBar.SetDragRectangles(new RectInt32[] { new RectInt32(0, 0, 0, 0) });
            await Task.Delay(200);
        }
    }
}
