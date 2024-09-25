using Microsoft.UI.Xaml.Controls;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace RSDK.AnimationEditor.Experimental.Content.Views.Other
{
    public sealed partial class NewFileDialog : ContentDialog
    {
        public NewFileDialog()
        {
            this.InitializeComponent();
        }

        private void vs_selected(object sender, SelectionChangedEventArgs e)
        {
            if (vs.SelectedItem != null)
            {
                IsPrimaryButtonEnabled = true;
            }
            else
            {
                IsPrimaryButtonEnabled = false;
            }
        }
    }
}
