#pragma once

#pragma push_macro("GetCurrentTime")
#undef GetCurrentTime

#include "ChatPage.g.h"

#pragma pop_macro("GetCurrentTime")

namespace winrt::Messenger::implementation
{
    struct ChatPage : ChatPageT<ChatPage>
    {
        ChatPage();
    };
}

namespace winrt::Messenger::factory_implementation
{
    struct ChatPage : ChatPageT<ChatPage, implementation::ChatPage> { };
}
