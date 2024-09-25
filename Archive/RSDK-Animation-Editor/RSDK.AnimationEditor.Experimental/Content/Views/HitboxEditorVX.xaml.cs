using Microsoft.UI;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Media;
using RSDK.AnimationEditor.Experimental.Content.ViewModels;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace RSDK.AnimationEditor.Experimental.Content.Views
{
    /// <summary>
    /// An empty window that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class HitboxEditorVX : Window
    {
        public HitboxV3EditorViewModel ViewModel => rootGrid.DataContext as HitboxV3EditorViewModel;

        public HitboxEditorVX(MainViewModel vm)
        {
            InitializeComponent();
            rootGrid.DataContext = new HitboxV3EditorViewModel(vm);

            Title = "Hitbox Manager";

            AppWindow.TitleBar.ExtendsContentIntoTitleBar = true;
            AppWindow.TitleBar.ButtonBackgroundColor = Colors.Transparent;
            AppWindow.TitleBar.ButtonInactiveBackgroundColor = Colors.Transparent;

            AppWindow.Resize(new Windows.Graphics.SizeInt32 { Width = 650, Height = 480 });

            SystemBackdrop = new MicaBackdrop();

            AppTitleBar.Padding = new Thickness(0, 0, AppWindow.TitleBar.RightInset, 0);

            //ThemeHelper.Initialize();
            //rootGrid.RequestedTheme = ThemeHelper.RootTheme;
        }

        private void AddHitbox(object sender, RoutedEventArgs e)
        {
            ViewModel.AddHitboxEntry();
        }

        private void RemoveHitbox(object sender, RoutedEventArgs e)
        {
            ViewModel.RemoveHitboxEntry();
        }

        private void List_SelectionChanged(object sender, Microsoft.UI.Xaml.Controls.SelectionChangedEventArgs e)
        {
            // I'll replace this later
            if (ViewModel.AnimationsUsed == null)
            {
                NoItems.Visibility = Visibility.Visible;
                UsedAnimList.Visibility = Visibility.Collapsed;
            }
            else
            {
                NoItems.Visibility = Visibility.Collapsed;
                UsedAnimList.Visibility = Visibility.Visible;
            }
        }
    }
}
