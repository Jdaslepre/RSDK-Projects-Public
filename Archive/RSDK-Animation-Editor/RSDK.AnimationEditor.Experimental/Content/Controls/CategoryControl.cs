using Microsoft.UI.Input;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media.Animation;
using System;

namespace RSDK.AnimationEditor.Experimental.Content.Controls
{
    public sealed class CategoryControl : Control
    {
        public static readonly DependencyProperty TitleProperty =
            DependencyProperty.Register("Title", typeof(string), typeof(CategoryControl), new PropertyMetadata(string.Empty));

        public static readonly DependencyProperty IsExpandedProperty =
            DependencyProperty.Register("IsExpanded", typeof(bool), typeof(CategoryControl), new PropertyMetadata(false, OnIsExpandedChanged));

        public static readonly DependencyProperty ContentProperty =
            DependencyProperty.Register("Content", typeof(object), typeof(CategoryControl), new PropertyMetadata(null));

        public event EventHandler Expanded;
        public event EventHandler Unexpanded;
        public event EventHandler CategoryClicked;

        private CheckBox expanderCheckBox;
        private Border titleBorder;
        private ContentPresenter contentPresenter;

        public CategoryControl()
        {
            DefaultStyleKey = typeof(CategoryControl);
        }

        public string Title
        {
            get { return (string)GetValue(TitleProperty); }
            set { SetValue(TitleProperty, value); }
        }

        public bool IsExpanded
        {
            get { return (bool)GetValue(IsExpandedProperty); }
            set { SetValue(IsExpandedProperty, value); }
        }

        public object Content
        {
            get { return GetValue(ContentProperty); }
            set { SetValue(ContentProperty, value); }
        }

        protected override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            expanderCheckBox = GetTemplateChild("ExpanderCheckBox") as CheckBox;
            titleBorder = GetTemplateChild("TitleBorder") as Border;
            contentPresenter = GetTemplateChild("ContentPresenter") as ContentPresenter;

            if (expanderCheckBox != null)
            {
                expanderCheckBox.Checked += ExpanderCheckBox_Checked;
                expanderCheckBox.Unchecked += ExpanderCheckBox_Unchecked;
            }

            if (titleBorder != null)
            {
                titleBorder.PointerPressed += OnCategoryClicked;
            }

            UpdateCheckbox();
            UpdateContentVisibility();
        }

        private void ExpanderCheckBox_Checked(object sender, RoutedEventArgs e)
        {
            IsExpanded = true;
            Expanded?.Invoke(this, EventArgs.Empty);
            UpdateContentVisibility();
            //PlayAddDeleteThemeTransition();
        }

        private void ExpanderCheckBox_Unchecked(object sender, RoutedEventArgs e)
        {
            IsExpanded = false;
            Unexpanded?.Invoke(this, EventArgs.Empty);
            UpdateContentVisibility();
            //PlayAddDeleteThemeTransition();
        }

        private static void OnIsExpandedChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var categoryControl = (CategoryControl)d;
            categoryControl.UpdateCheckbox();
            categoryControl.UpdateContentVisibility();
        }

        private void UpdateCheckbox()
        {
            if (expanderCheckBox != null)
            {
                expanderCheckBox.IsChecked = IsExpanded;
            }
        }

        private void UpdateContentVisibility()
        {
            if (contentPresenter != null)
            {
                contentPresenter.Visibility = IsExpanded ? Visibility.Visible : Visibility.Collapsed;
                if (contentPresenter.Visibility == Visibility.Visible)
                {
                    //PlayAddDeleteThemeTransition();
                }
            }
        }

        private void OnCategoryClicked(object sender, PointerRoutedEventArgs e)
        {
            if (e.Pointer.PointerDeviceType == PointerDeviceType.Mouse)
            {
                var properties = e.GetCurrentPoint(titleBorder).Properties;
                if (properties.IsLeftButtonPressed)
                {
                    CategoryClicked?.Invoke(this, EventArgs.Empty);
                }
            }
            else if (e.Pointer.PointerDeviceType == PointerDeviceType.Touch)
            {
                CategoryClicked?.Invoke(this, EventArgs.Empty);
            }
        }

        private void PlayAddDeleteThemeTransition()
        {
            if (contentPresenter != null)
            {
                var transition = new TransitionCollection();
                transition.Add(new AddDeleteThemeTransition());
                contentPresenter.ContentTransitions = transition;
            }
        }
    }
}




















/*
using Microsoft.UI.Input;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Input;
using System;

namespace RSDK.AnimationEditor.Experimental.Content.Controls
{
    public sealed class CategoryControl : Control
    {
        public static readonly DependencyProperty TitleProperty =
            DependencyProperty.Register("Title", typeof(string), typeof(CategoryControl), new PropertyMetadata(string.Empty));

        public static readonly DependencyProperty IsExpandedProperty =
            DependencyProperty.Register("IsExpanded", typeof(bool), typeof(CategoryControl), new PropertyMetadata(false, OnIsExpandedChanged));

        public static readonly DependencyProperty ContentProperty =
            DependencyProperty.Register("Content", typeof(object), typeof(CategoryControl), new PropertyMetadata(null));

        public event EventHandler Expanded;
        public event EventHandler Unexpanded;
        public event EventHandler CategoryClicked;

        private CheckBox expanderCheckBox;
        private Border titleBorder;
        private ContentPresenter contentPresenter;

        public CategoryControl()
        {
            DefaultStyleKey = typeof(CategoryControl);
        }

        public string Title
        {
            get { return (string)GetValue(TitleProperty); }
            set { SetValue(TitleProperty, value); }
        }

        public bool IsExpanded
        {
            get { return (bool)GetValue(IsExpandedProperty); }
            set { SetValue(IsExpandedProperty, value); }
        }

        public object Content
        {
            get { return GetValue(ContentProperty); }
            set { SetValue(ContentProperty, value); }
        }

        protected override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            expanderCheckBox = GetTemplateChild("ExpanderCheckBox") as CheckBox;
            titleBorder = GetTemplateChild("TitleBorder") as Border;
            contentPresenter = GetTemplateChild("ContentPresenter") as ContentPresenter;

            if (expanderCheckBox != null)
            {
                expanderCheckBox.Checked += ExpanderCheckBox_Checked;
                expanderCheckBox.Unchecked += ExpanderCheckBox_Unchecked;
            }

            if (titleBorder != null)
            {
                titleBorder.PointerPressed += OnCategoryClicked;
            }

            UpdateCheckbox();
            UpdateContentVisibility();
        }

        private void ExpanderCheckBox_Checked(object sender, RoutedEventArgs e)
        {
            IsExpanded = true;
            Expanded?.Invoke(this, EventArgs.Empty);
            UpdateContentVisibility();
        }

        private void ExpanderCheckBox_Unchecked(object sender, RoutedEventArgs e)
        {
            IsExpanded = false;
            Unexpanded?.Invoke(this, EventArgs.Empty);
            UpdateContentVisibility();
        }

        private static void OnIsExpandedChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var categoryControl = (CategoryControl)d;
            categoryControl.UpdateCheckbox();
            categoryControl.UpdateContentVisibility();
        }

        private void UpdateCheckbox()
        {
            if (expanderCheckBox != null)
            {
                expanderCheckBox.IsChecked = IsExpanded;
            }
        }

        private void UpdateContentVisibility()
        {
            if (contentPresenter != null)
            {
                contentPresenter.Visibility = IsExpanded ? Visibility.Visible : Visibility.Collapsed;
            }
        }

        private void OnCategoryClicked(object sender, PointerRoutedEventArgs e)
        {
            if (e.Pointer.PointerDeviceType == PointerDeviceType.Mouse)
            {
                var properties = e.GetCurrentPoint(titleBorder).Properties;
                if (properties.IsLeftButtonPressed)
                {
                    CategoryClicked?.Invoke(this, EventArgs.Empty);
                }
            }
            else if (e.Pointer.PointerDeviceType == PointerDeviceType.Touch)
            {
                CategoryClicked?.Invoke(this, EventArgs.Empty);
            }
        }
    }
}
*/