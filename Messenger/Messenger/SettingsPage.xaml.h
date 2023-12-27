#pragma once

#pragma push_macro("GetCurrentTime")
#undef GetCurrentTime

#include "SettingsPage.g.h"

#pragma pop_macro("GetCurrentTime")

namespace winrt::Messenger::implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage>
    {
        SettingsPage();
    };
}

namespace winrt::Messenger::factory_implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage, implementation::SettingsPage> { };
}
