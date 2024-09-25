using Microsoft.UI;
using Microsoft.UI.Windowing;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media;
using RSDK.AnimationEditor.Content.Views;
using System;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using Windows.Graphics;
using WinRT.Interop;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace RSDK.AnimationEditor
{
    /// <summary>
    /// An empty window that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class TabbedWindow : Window
    {
        public static TabView tabs { get; set; }
        //private const string DataIdentifier = "tabba";
        public TabbedWindow()
        {
            this.InitializeComponent();
            tabs = Tabs;
            Title = "RSDK Animation Editor";

            ExtendsContentIntoTitleBar = true;

            //AppWindow.TitleBar.ExtendsContentIntoTitleBar = true;
            //AppWindow.TitleBar.ButtonBackgroundColor = Colors.Transparent;
            //AppWindow.TitleBar.ButtonInactiveBackgroundColor = Colors.Transparent;

            var manager = WinUIEx.WindowManager.Get(this);
            manager.PersistenceId = "Persistance";
            manager.MinWidth = 500;
            manager.MinHeight = 350;

            //var backdrop = new MicaBackdrop();
            //backdrop.Kind = Microsoft.UI.Composition.SystemBackdrops.MicaKind.BaseAlt;
            //SystemBackdrop = backdrop;

            CreateNewTab();
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
            //await Task.Delay(500);
            // - (int)wTitleInset.ActualWidth
            //int x = AppWindow.Size.Width - (int)e.NewSize.Width - 16;
            //int y = 0;
            //int width = (int)e.NewSize.Width;
            //int height = (int)e.NewSize.Height;
            //var dragrects = new RectInt32[] { new RectInt32(x, y, width, height) };

            //AppWindow.TitleBar.SetDragRectangles(dragrects);
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
            UnloadObject(args.Tab);
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

        private void CreateNewTab()
        {
            var newTab = new TabViewItem();
            newTab.Header = "New tab";
            newTab.Content = new MainPage();
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
    }
}