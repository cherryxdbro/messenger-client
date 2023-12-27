#pragma once

#pragma push_macro("GetCurrentTime")
#undef GetCurrentTime

#include "ConnectionPage.g.h"

#pragma pop_macro("GetCurrentTime")

#include "Capsulator.h"
#include "Signer.h"

namespace winrt::Messenger::implementation
{
    struct ConnectionPage : ConnectionPageT<ConnectionPage>
    {
        ConnectionPage();

        void connectButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        Capsulator::KyberKeyPair kyberKeyPair;
        Signer::DilithiumKeyPair dilithiumKeyPair;
    };
}

namespace winrt::Messenger::factory_implementation
{
    struct ConnectionPage : ConnectionPageT<ConnectionPage, implementation::ConnectionPage> { };
}
