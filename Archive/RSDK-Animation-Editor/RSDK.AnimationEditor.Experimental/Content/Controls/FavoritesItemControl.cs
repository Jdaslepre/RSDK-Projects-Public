using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;

namespace RSDK.AnimationEditor.Experimental.Content.Controls
{
    public class FavoritesItemControl : Control
    {
        public FavoritesItemControl()
        {
            DefaultStyleKey = typeof(FavoritesItemControl);
        }

        public static readonly DependencyProperty TitleProperty =
            DependencyProperty.Register("Title", typeof(string), typeof(FavoritesItemControl), new PropertyMetadata(string.Empty));

        public string Title
        {
            get { return (string)GetValue(TitleProperty); }
            set { SetValue(TitleProperty, value); }
        }

        public event RoutedEventHandler Unfavorited;

        protected virtual void OnUnfavorited()
        {
            RoutedEventArgs args = new RoutedEventArgs();
            Unfavorited?.Invoke(this, args);
        }

        protected override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            Button unfavoriteButton = GetTemplateChild("UnfavoriteButton") as Button;
            if (unfavoriteButton != null)
            {
                unfavoriteButton.Click += (sender, e) => OnUnfavorited();
            }
        }
    }
}
