using Microsoft.UI.Xaml;
using RSDK.AnimationEditor.Content;
using System.Runtime.InteropServices;
using Windows.Storage;


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace RSDK.AnimationEditor
{
    /// <summary>
    /// Provides application-specific behavior to supplement the default Application class.
    /// </summary>
    public partial class App : Application
    {
        /// <summary>
        /// Initializes the singleton application object.  This is the first line of authored code
        /// executed, and as such is the logical equivalent of main() or WinMain().
        /// </summary>

        [DllImport("uxtheme.dll", EntryPoint = "#135", SetLastError = true, CharSet = CharSet.Unicode)]
        private static extern int SetPreferredAppMode(int preferredAppMode);
        ApplicationDataContainer localSettings = ApplicationData.Current.LocalSettings;
        public App()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Invoked when the application is launched normally by the end user.  Other entry points
        /// will be used such as when the application is launched to open a specific file.
        /// </summary>
        /// <param name="args">Details about the launch request and process.</param>

        protected override void OnLaunched(LaunchActivatedEventArgs args)
        {
            bool isTabsEnabled = localSettings.Values["isTabsEnabled"]?.ToString() == "yep";
            Window window;
            if (isTabsEnabled)
            {
                window = new TabbedWindow();
            }
            else
            {
                window = new MainWindow();
            }
            window.Activate();
            SetPreferredAppMode(1);
            WindowHelper.TrackWindow(window);
        }
    }
}