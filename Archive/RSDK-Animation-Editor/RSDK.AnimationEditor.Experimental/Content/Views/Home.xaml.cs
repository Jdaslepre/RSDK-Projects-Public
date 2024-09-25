using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Input;
using RSDK.AnimationEditor.Experimental.Content.Controls;
using System;
using System.Threading.Tasks;
using Windows.Foundation;
using Windows.Storage.AccessCache;

namespace RSDK.AnimationEditor.Experimental.Content.Views
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class Home : Page
    {
        public Home()
        {
            this.InitializeComponent();
            SetupRecentFiles();
            contentGrid.PointerPressed += SelectionCanvas_PointerPressed;
            contentGrid.PointerMoved += SelectionCanvas_PointerMoved;
            contentGrid.PointerReleased += SelectionCanvas_PointerReleased;
            //ThemeHelper.Initialize();
            //RequestedTheme = ThemeHelper.RootTheme;
        }

        private async Task SetupRecentFiles()
        {
            foreach (AccessListEntry entry in StorageApplicationPermissions.MostRecentlyUsedList.Entries)
            {
                var file = await StorageApplicationPermissions.MostRecentlyUsedList.GetFileAsync(entry.Token);
                var item = new ListViewItem();
                //menuflyoutitem.Icon = new SymbolIcon(Symbol.Document);
                item.Content = $"{file.Name} - {(file.FileType == ".ani" ? "RSDKv4" : file.FileType == ".bin" ? "RSDKv5" : "Unknown")}";
                //menuflyoutitem.Click += async (sender, args) => { await Open(false, file); };

                recentList.Items.Add(item);
            }

            //RecentClear.Click +=
            //(sender, args) =>
            //{
            //    StorageApplicationPermissions.MostRecentlyUsedList.Clear();
            //};
        }

        private bool isDragging = false;
        private Point startPoint;

        private void SelectionCanvas_PointerPressed(object sender, PointerRoutedEventArgs e)
        {
            startPoint = e.GetCurrentPoint(SelectionCanvas).Position;
            isDragging = true;
        }

        private void SelectionCanvas_PointerMoved(object sender, PointerRoutedEventArgs e)
        {
            if (isDragging)
            {
                Point currentPoint = e.GetCurrentPoint(SelectionCanvas).Position;

                double left = Math.Min(startPoint.X, currentPoint.X);
                double top = Math.Min(startPoint.Y, currentPoint.Y);
                double width = Math.Abs(currentPoint.X - startPoint.X);
                double height = Math.Abs(currentPoint.Y - startPoint.Y);

                Canvas.SetLeft(SelectionRectangle, left);
                Canvas.SetTop(SelectionRectangle, top);
                SelectionRectangle.Width = width;
                SelectionRectangle.Height = height;

                SelectionCanvas.Visibility = Microsoft.UI.Xaml.Visibility.Visible;
            }
        }

        private void SelectionCanvas_PointerReleased(object sender, PointerRoutedEventArgs e)
        {
            isDragging = false;
            SelectionCanvas.Visibility = Microsoft.UI.Xaml.Visibility.Collapsed;
        }

        private void CategoryControl_CategoryClicked(object sender, EventArgs e)
        {
            recentList.SelectAll();
        }

        private void FavoritesItemControl_Unfavorited(object sender, Microsoft.UI.Xaml.RoutedEventArgs e)
        {
            if (sender is FavoritesItemControl itemControl)
            {
                if (itemControl.Parent is Panel parentPanel)
                {
                    parentPanel.Children.Remove(itemControl);
                    //UnloadObject(itemControl);
                }
            }
        }

    }
}
