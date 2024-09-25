using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using RSDK.AnimationEditor.Experimental.Content.ViewModels;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace RSDK.AnimationEditor.Experimental.Content.Views
{
    /// <summary>
    /// An empty window that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class HitboxEditorV5 : UserControl
    {
        public HitboxV5EditorViewModel ViewModel => root.DataContext as HitboxV5EditorViewModel;
        public HitboxEditorV5(MainViewModel vm)
        {
            InitializeComponent();
            root.DataContext = new HitboxV5EditorViewModel(vm);
            //ExtendsContentIntoTitleBar = true;
            //SetTitleBar(AppTitleBar);
        }

        private void ButtonAdd_Click(object sender, RoutedEventArgs e)
        {
            ViewModel.HitboxTypeItems.Add("EMPTY");
        }

        private void ButtonRemove_Click(object sender, RoutedEventArgs e)
        {
            if (ViewModel.IsValueSelected)
                ViewModel.HitboxTypeItems.RemoveAt(ViewModel.SelectedIndex);
        }

        private void TextBox_LostFocus(object sender, RoutedEventArgs e)
        {
            if (sender is TextBox textBox)
            {
                ViewModel.UpdateList(textBox.Text);
            }
        }


    }
}
