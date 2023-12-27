#include "pch.h"
#include "MainPage.xaml.h"
#if __has_include("MainPage.g.cpp")
#include "MainPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

#include "Pages.h"

namespace winrt::Messenger::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
    }

    void MainPage::NavigationView_SelectionChanged(Controls::NavigationView const&, Controls::NavigationViewSelectionChangedEventArgs const& args)
    {
        if (args.IsSettingsSelected())
        {
            contentFrame().Navigate(xaml_typename<Messenger::SettingsPage>());
        }
        else
        {
            switch (getPageByTag(unbox_value<hstring>(args.SelectedItemContainer().Tag())))
            {
            case Pages::ChatPage:
                contentFrame().Navigate(xaml_typename<Messenger::ChatPage>(), box_value(contentFrame().CurrentSourcePageType()));
                break;
            case Pages::ConnectionPage:
                contentFrame().Navigate(xaml_typename<Messenger::ConnectionPage>(), box_value(contentFrame().CurrentSourcePageType()));
                break;
            }
        }
    }
}
