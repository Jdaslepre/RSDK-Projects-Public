using Microsoft.UI;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Media;
using RSDK.AnimationEditor.Experimental.Content.ViewModels;
using System;
using System.IO;
using Windows.Storage.Pickers;
using WinRT.Interop;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace RSDK.AnimationEditor.Experimental.Content.Views
{
    /// <summary>
    /// An empty window that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class TextureLibrary : Window
    {
        public string BasePath { get; private set; }
        public TextureWindowViewModel ViewModel => rootGrid.DataContext as TextureWindowViewModel;
        public MainViewModel MainViewModel { get; }
        public int SelectedIndex
        {
            get => ViewModel.SelectedIndex;
            set => ViewModel.SelectedIndex = value;
        }

        /*
        public TextureManager(MainViewModel mainViewModel)
        {
            InitializeComponent();
            MainViewModel = mainViewModel;
            rootGrid.DataContext = new TextureWindowViewModel(mainViewModel, BasePath);
        }
        */

        public TextureLibrary(MainViewModel mainViewModel, string basePath)
        {
            InitializeComponent();

            BasePath = basePath;
            MainViewModel = mainViewModel;
            rootGrid.DataContext = new TextureWindowViewModel(mainViewModel, BasePath);

            Title = "Texture Library";

            AppWindow.TitleBar.ExtendsContentIntoTitleBar = true;
            AppWindow.TitleBar.ButtonBackgroundColor = Colors.Transparent;
            AppWindow.TitleBar.ButtonInactiveBackgroundColor = Colors.Transparent;

            AppWindow.Resize(new Windows.Graphics.SizeInt32 { Width = 784, Height = 554 });

            SystemBackdrop = new MicaBackdrop();

            PaneColumn.Width = new GridLength(320);

            //this.CenterOnScreen();

            //ThemeHelper.Initialize();
            //rootGrid.RequestedTheme = ThemeHelper.RootTheme;

        }

        #region Functionality

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
            Dialog.Content = $"Do you want to remove {ViewModel.SelectedValue} from {MainViewModel.FileNameString}?";
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

    }
}
