using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Shapes;
using RSDK.AnimationEditor.Experimental.Content.ViewModels;
using System.Linq;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace RSDK.AnimationEditor.Experimental.Experimental.Content.Views
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class TabbedWindowContent : Page
    {
        public static Grid maincontent { get; set; }
        public static TabView tabs { get; set; }
        public static Rectangle dragrect { get; set; }
        public static Page settings { get; set; }
        public static Page hmm { get; set; }
        public TabbedWindowContent()
        {
            this.InitializeComponent();
            maincontent = MainContent;
            tabs = Tabs;
            dragrect = wDragRect;
            //settings = Settings;
            hmm = this;
            CreateNewTab();
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


        /*
        private void CreateNewTab()
        {
            var newTab = new TabViewItem();
            newTab.DataContext = new MainViewModel();
            Binding stringBinding = new Binding();
            stringBinding.Source = newTab.DataContext;
            stringBinding.Path = new PropertyPath("TitleString");
            stringBinding.Mode = BindingMode.TwoWay;
            stringBinding.UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged;
            BindingOperations.SetBinding(newTab, TabViewItem.HeaderProperty, stringBinding);
            Tabs.TabItems.Add(newTab);
            Tabs.SelectedItem = newTab;
        }
        */

        #endregion

        private void Tabs_TabItemsChanged(TabView sender, Windows.Foundation.Collections.IVectorChangedEventArgs args)
        {
            if (Tabs.TabItems.Count <= 0)
            {
                WindowHelper.GetWindowForElement(this).Close();
            }
        }
    }
}
