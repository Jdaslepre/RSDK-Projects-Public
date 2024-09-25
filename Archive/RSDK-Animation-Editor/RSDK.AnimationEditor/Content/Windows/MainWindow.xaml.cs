using Microsoft.UI;
using Microsoft.UI.Windowing;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Media;
using RSDK.AnimationEditor.Content.Views;

namespace RSDK.AnimationEditor
{
    public partial class MainWindow : Window
    {
        public static MainWindow XamlWindow { get; set; }
        public MainWindow()
        {
            InitializeComponent();
            XamlWindow = this;

            Title = "RSDK Animation Editor";

            //AppWindow.TitleBar.ExtendsContentIntoTitleBar = true;
            //AppWindow.TitleBar.ButtonBackgroundColor = Colors.Transparent;
            //AppWindow.TitleBar.ButtonInactiveBackgroundColor = Colors.Transparent;

            ExtendsContentIntoTitleBar = true;

            var manager = WinUIEx.WindowManager.Get(this);
            manager.PersistenceId = "Persistance";
            manager.MinWidth = 500;
            manager.MinHeight = 350;

            //SystemBackdrop = new MicaBackdrop();
            var Mica = new MicaBackdropHelper();
            Mica.Kind = MicaKind.Base;
            Mica.TrySetMicaBackdrop(this);


            rootFrame.Navigate(typeof(MainPage));
        }
    }
}
