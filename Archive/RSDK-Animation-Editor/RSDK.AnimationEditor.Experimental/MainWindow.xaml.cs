using Microsoft.UI;
using Microsoft.UI.Windowing;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media;
using Microsoft.UI.Xaml.Shapes;
using RSDK.AnimationEditor.Experimental.Content.ViewModels;
using RSDK.AnimationEditor.Experimental.Content.Views;
using System;
using System.Linq;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using Windows.Graphics;
using WinRT.Interop;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace RSDK.AnimationEditor.Experimental
{
    /// <summary>
    /// An empty window that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainWindow : Window
    {
        public static Grid rootgrid { get; set; }
        public static Grid maincontent { get; set; }
        public static TabView tabs { get; set; }
        public static Rectangle dragrect { get; set; }
        public static Settings settingsPage { get; set; }
        public MainWindow()
        {
            this.InitializeComponent();
            rootgrid = rootGrid;
            maincontent = MainContent;
            tabs = Tabs;
            dragrect = wDragRect;
            settingsPage = new Settings();
            CreateNewTab();

            Title = "RSDK Animation Editor";

            AppWindow.TitleBar.ExtendsContentIntoTitleBar = true;
            AppWindow.TitleBar.ButtonBackgroundColor = Colors.Transparent;
            AppWindow.TitleBar.ButtonInactiveBackgroundColor = Colors.Transparent;

            var manager = WinUIEx.WindowManager.Get(this);
            manager.PersistenceId = "Persistance";
            manager.MinWidth = 500;
            manager.MinHeight = 350;

            var Mica = new MicaBackdrop();
            Mica.Kind = Microsoft.UI.Composition.SystemBackdrops.MicaKind.BaseAlt;
            SystemBackdrop = Mica;

            MainPage.settingsbutton.Click += Settings_Click;
        }

        public void Settings_Click(object sender, RoutedEventArgs e)
        {
            MainContent.Opacity = 0;
            rootGrid.Children.Add(settingsPage);
        }

        #region TabView function related things

        #region NewTab
        private void TabAddButton_(TabView sender, object args)
        {
            CreateNewTab();
        }
        private void NewTabAccelerator_(KeyboardAccelerator sender, KeyboardAcceleratorInvokedEventArgs args)
        {
            CreateNewTab();
            args.Handled = true;
        }
        #endregion
        #region CloseTab
        private void TabCloseRequested_(TabView sender, TabViewTabCloseRequestedEventArgs args)
        {
            sender.TabItems.Remove(args.Tab);
        }
        private void CloseTabAccelerator_(KeyboardAccelerator sender, KeyboardAcceleratorInvokedEventArgs args)
        {
            var InvokedTabView = (args.Element as TabView);
            if (((TabViewItem)InvokedTabView.SelectedItem).IsClosable)
            {
                InvokedTabView.TabItems.Remove(InvokedTabView.SelectedItem);
            }
            args.Handled = true;
        }
        #endregion

        private void Tabs_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (e.AddedItems != null && e.AddedItems.Count > 0)
            {
                var selectedTab = e.AddedItems.FirstOrDefault() as TabViewItem;
                var selectedTabDataContext = selectedTab.DataContext;
                MainPage.DataContext = selectedTabDataContext;
            }
        }

        private void CreateNewTab()
        {
            var newTab = new TabViewItem
            {
                DataContext = new MainViewModel()
            };
            newTab.SetBinding(TabViewItem.HeaderProperty, new Binding()
            {
                Path = new PropertyPath("TitleString"),
                Mode = BindingMode.TwoWay,
                UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
            });
            Tabs.TabItems.Add(newTab);
            Tabs.SelectedItem = newTab;
        }

        #endregion

        private void Tabs_TabItemsChanged(TabView sender, Windows.Foundation.Collections.IVectorChangedEventArgs args)
        {
            if (Tabs.TabItems.Count <= 0)
            {
                Close();
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
            await Task.Delay(500);

            double scaleAdjustment = GetScaleAdjustment();

            double x = Math.Round((AppWindow.Size.Width - e.NewSize.Width) / scaleAdjustment);
            double y = 0;
            double width = Math.Round(e.NewSize.Width * scaleAdjustment);
            double height = Math.Round(e.NewSize.Height * scaleAdjustment);

            var dragrects = new RectInt32[] { new RectInt32((int)x, (int)y, (int)width, (int)height) };

            AppWindow.TitleBar.SetDragRectangles(dragrects);
        }



    }
}