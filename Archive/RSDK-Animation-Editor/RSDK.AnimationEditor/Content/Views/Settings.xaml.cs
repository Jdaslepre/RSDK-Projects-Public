using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Media.Animation;
using System;
using Windows.ApplicationModel;
using Windows.Storage;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace RSDK.AnimationEditor.Content.Views
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

            String tabs = localSettings.Values["isTabsEnabled"] as string;
            if (tabs == "yep")
            {
                tabToggle.IsOn = true;
            }
            else
            {
                FindName("AppTitleBar");
            }

        }

        private void _SizeChanged(object sender, Microsoft.UI.Xaml.SizeChangedEventArgs e)
        {

            //I know this is terrible, don't blame pls ;-;
            //I'll find a way to define this in xaml eventually

            if (ActualWidth > 960)
            {
                //Fully expanded
                Grid.SetRow(AboutContainer, 0);
                Grid.SetColumn(AboutContainer, 1);
                AboutContainer.Margin = new Thickness(0, 8, 0, 8);
                ContentContainer.ColumnSpacing = 56;
            }
            else if (ActualWidth < 960)
            {
                if (ActualWidth != 645)
                {
                    //Medium state
                    Grid.SetRow(AboutContainer, 1);
                    Grid.SetColumn(AboutContainer, 0);
                    AboutContainer.Margin = new Thickness(0, 24, 0, 0);
                    ContentContainer.ColumnSpacing = 0;
                }
                if (ActualWidth > 645)
                {
                    //Check if the state is compact before reverting changes
                    //we'll just use the FontSize :)
                    if (SettingHeader.FontSize == 28)
                    {
                        RootContainer.Margin = new Thickness(0, 28, 0, 0);
                        ContentContainer.Margin = new Thickness(52, 24, 52, 24);
                        SettingHeader.Margin = new Thickness(52, 0, 0, 0);
                        SettingHeader.FontSize = 40;
                    }
                }
                if (ActualWidth < 645)
                {
                    //Compact state
                    RootContainer.Margin = new Thickness(0, 16, 0, 0);
                    ContentContainer.Margin = new Thickness(16);
                    SettingHeader.Margin = new Thickness(16, 0, 0, 0);
                    SettingHeader.FontSize = 28;
                }
            }

        }

        private void Back_Click(object sender, Microsoft.UI.Xaml.RoutedEventArgs e)
        {
            if (Frame.CanGoBack)
            {
                Frame.GoBack();
            }
            else
            {
                Frame.Navigate(typeof(MainPage), null, new DrillInNavigationTransitionInfo());
            }
        }

        private void Theme_Checked(object sender, RoutedEventArgs e)
        {
            /*
            if (sender is RadioButton radio)
            {
                string tag = radio.Tag as string;
                switch (tag)
                {
                    case "1":
                        App.Current.RequestedTheme = ApplicationTheme.Light;
                        break;
                    case "2":
                        App.Current.RequestedTheme = ApplicationTheme.Dark;
                        break;
                    case "3":
                        break;
                }
            }
            */
        }

        private void tabs_Toggled(object sender, RoutedEventArgs e)
        {
            ToggleSwitch toggleSwitch = sender as ToggleSwitch;
            if (toggleSwitch != null)
            {
                if (toggleSwitch.IsOn == true)
                {
                    localSettings.Values["isTabsEnabled"] = "yep";
                }
                else
                {
                    localSettings.Values["isTabsEnabled"] = "nope";
                }
            }
        }
    }
}
