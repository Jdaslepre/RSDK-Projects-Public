using Microsoft.UI.Xaml;
using RSDK.AnimationEditor.Content;
using System.Runtime.InteropServices;
using WinRT;

namespace RSDK.AnimationEditor
{
    public enum MicaKind
    {
        Base,
        BaseAlt
    }
    public class MicaBackdropHelper
    {
        private WindowsSystemDispatcherQueueHelper m_wsdqHelper;
        private Microsoft.UI.Composition.SystemBackdrops.MicaController m_micaController;
        public MicaKind Kind { get; set; }
        private Microsoft.UI.Composition.SystemBackdrops.SystemBackdropConfiguration m_configurationSource;
        private Window window; // Store the window object for later use

        public bool TrySetMicaBackdrop(Window window)
        {
            if (Microsoft.UI.Composition.SystemBackdrops.MicaController.IsSupported())
            {
                m_wsdqHelper = new WindowsSystemDispatcherQueueHelper();
                m_wsdqHelper.EnsureWindowsSystemDispatcherQueueController();

                // Store the window object as a class member
                this.window = window;

                // Hooking up the policy object
                m_configurationSource = new Microsoft.UI.Composition.SystemBackdrops.SystemBackdropConfiguration();
                window.Activated += Window_Activated;
                window.Closed += Window_Closed;
                ((FrameworkElement)window.Content).ActualThemeChanged += Window_ThemeChanged;

                // Initial configuration state.
                m_configurationSource.IsInputActive = true;
                SetConfigurationSourceTheme();

                m_micaController = new Microsoft.UI.Composition.SystemBackdrops.MicaController();

                switch (Kind)
                {
                    case MicaKind.Base: m_micaController.Kind = Microsoft.UI.Composition.SystemBackdrops.MicaKind.Base; break;
                    case MicaKind.BaseAlt: m_micaController.Kind = Microsoft.UI.Composition.SystemBackdrops.MicaKind.BaseAlt; break;
                }

                // Enable the system backdrop.
                // Note: Be sure to have "using WinRT;" to support the Window.As<...>() call.
                m_micaController.AddSystemBackdropTarget(window.As<Microsoft.UI.Composition.ICompositionSupportsSystemBackdrop>());
                m_micaController.SetSystemBackdropConfiguration(m_configurationSource);
                return true; // succeeded
            }

            return false; // Mica is not supported on this system
        }

        private void Window_Activated(object sender, WindowActivatedEventArgs args)
        {
            m_configurationSource.IsInputActive = args.WindowActivationState != WindowActivationState.Deactivated;
        }

        private void Window_Closed(object sender, WindowEventArgs args)
        {
            // Make sure any Mica/Acrylic controller is disposed so it doesn't try to
            // use this closed window.
            if (m_micaController != null)
            {
                m_micaController.Dispose();
                m_micaController = null;
            }
            window.Activated -= Window_Activated;
            m_configurationSource = null;
        }

        private void Window_ThemeChanged(FrameworkElement sender, object args)
        {
            if (m_configurationSource != null)
            {
                SetConfigurationSourceTheme();
            }
        }

        private void SetConfigurationSourceTheme()
        {
            switch (((FrameworkElement)window.Content).ActualTheme)
            {
                case ElementTheme.Dark: m_configurationSource.Theme = Microsoft.UI.Composition.SystemBackdrops.SystemBackdropTheme.Dark; break;
                case ElementTheme.Light: m_configurationSource.Theme = Microsoft.UI.Composition.SystemBackdrops.SystemBackdropTheme.Light; break;
                case ElementTheme.Default: m_configurationSource.Theme = Microsoft.UI.Composition.SystemBackdrops.SystemBackdropTheme.Default; break;
            }
        }
    }
}
