#pragma once

#pragma push_macro("GetCurrentTime")
#undef GetCurrentTime

#include "MainWindow.g.h"

#pragma pop_macro("GetCurrentTime")

namespace winrt::Messenger::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();
    };
}

namespace winrt::Messenger::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow> { };
}
