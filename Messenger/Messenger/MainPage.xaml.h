#pragma once

#pragma push_macro("GetCurrentTime")
#undef GetCurrentTime

#include "MainPage.g.h"

#pragma pop_macro("GetCurrentTime")

namespace winrt::Messenger::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        void NavigationView_SelectionChanged(Microsoft::UI::Xaml::Controls::NavigationView const& sender, Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args);
    };
}

namespace winrt::Messenger::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage> { };
}
