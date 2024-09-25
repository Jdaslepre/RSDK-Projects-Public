using Microsoft.UI;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Media;
using RSDK.AnimationEditor.Content.ViewModels;
using WinUIEx;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace RSDK.AnimationEditor.Content.Views
{
    /// <summary>
    /// An empty window that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class HitboxManagerVX : WinUIEx.WindowEx
    {
        public HitboxV3EditorViewModel ViewModel => RootGrid.DataContext as HitboxV3EditorViewModel;

        public HitboxManagerVX(MainViewModel vm)
        {
            InitializeComponent();
            //SystemBackdrop = new MicaBackdrop();

            RootGrid.DataContext = new HitboxV3EditorViewModel(vm);

            //AppWindow.TitleBar.ExtendsContentIntoTitleBar = true;
            //AppWindow.TitleBar.ButtonBackgroundColor = Colors.Transparent;
            //AppWindow.TitleBar.ButtonInactiveBackgroundColor = Colors.Transparent;

            ExtendsContentIntoTitleBar = true;

            this.CenterOnScreen();
        }

        private void AddHitbox(object sender, RoutedEventArgs e)
        {
            ViewModel.AddHitboxEntry();
        }

        private void RemoveHitbox(object sender, RoutedEventArgs e)
        {
            ViewModel.RemoveHitboxEntry();
        }
    }
}
