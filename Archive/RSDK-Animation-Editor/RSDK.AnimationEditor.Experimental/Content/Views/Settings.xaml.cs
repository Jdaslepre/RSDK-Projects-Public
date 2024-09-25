using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using System.Diagnostics;
using Windows.ApplicationModel;
using Windows.Storage;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace RSDK.AnimationEditor.Experimental.Content.Views
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class Settings : Page
    {
        ApplicationDataContainer localSettings = ApplicationData.Current.LocalSettings;
        public static Grid SDragRegion { get; set; }
        public Settings()
        {
            InitializeComponent();
            SDragRegion = DragRegion;
            var Version = Package.Current.Id.Version;
            AppString.Text = $"RSDK Animation Editor {string.Format("{0}.{1}.{2}.{3}", Version.Major, Version.Minor, Version.Build, Version.Revision)}";
            var currentTheme = ThemeHelper.RootTheme;
            switch (currentTheme)
            {
                case ElementTheme.Light:
                    themeMode.SelectedIndex = 0;
                    break;
                case ElementTheme.Dark:
                    themeMode.SelectedIndex = 1;
                    break;
                case ElementTheme.Default:
                    themeMode.SelectedIndex = 2;
                    break;
            }
        }
        private void Page_Loaded(object sender, RoutedEventArgs e)
        {
            //rootGrid.Opacity = 1;
        }

        private async void Back_Click(object sender, RoutedEventArgs e)
        {
            if (MainWindow.settingsPage != null)
            {
                MainWindow.rootgrid.Children.Remove(MainWindow.settingsPage);
                MainWindow.maincontent.Opacity = 1;
            }
        }

        private void Theme_Checked(object sender, RoutedEventArgs e)
        {
            if (sender is RadioButton radio)
            {
                string tag = radio.Tag as string;
                switch (tag)
                {
                    case "1":
                        ThemeHelper.RootTheme = ElementTheme.Light;
                        break;
                    case "2":
                        ThemeHelper.RootTheme = ElementTheme.Dark;
                        break;
                    case "3":
                        ThemeHelper.RootTheme = ElementTheme.Default;
                        break;
                }
            }
        }

        private void feedback_Click(object sender, RoutedEventArgs e)
        {
            var procInfo = new ProcessStartInfo();
            procInfo.UseShellExecute = true;
            procInfo.FileName = "https://github.com/Lemonhandles/RSDK-Animation-Editor/issues/new";
            Process.Start(procInfo);
        }
    }
}
