#include "pch.h"
#include "ConnectionPage.xaml.h"
#if __has_include("ConnectionPage.g.cpp")
#include "ConnectionPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

#include "Cryptor.h"

extern "C"
{
    #include "randombytes.h"
}

namespace winrt::Messenger::implementation
{
    ConnectionPage::ConnectionPage()
    {
        InitializeComponent();
    }

    void ConnectionPage::connectButton_Click(Windows::Foundation::IInspectable const&, RoutedEventArgs const&)
    {
        if (unbox_value<hstring>(connectButton().Content()) != L"CHECK🌈")
        {
            kyberKeyPair = Capsulator::MakeKyberKeyPair();
            Capsulator::KyberCapsulated kyberCapsulated = Capsulator::KyberEncapsulateKey(kyberKeyPair.PublicKey);
            std::unique_ptr<uint8_t[]> sharedKey = Capsulator::KyberDecapsulateKey(kyberCapsulated.CipherText, kyberKeyPair.PrivateKey);
            if (Capsulator::KyberVerify(kyberCapsulated.SharedKey, sharedKey))
            {
                dilithiumKeyPair = Signer::MakeDilithiumKeyPair();
                std::unique_ptr<uint8_t[]> initializationVector1 = std::make_unique<uint8_t[]>(CRYPTO_BYTES);
                std::unique_ptr<uint8_t[]> initializationVector2 = std::make_unique<uint8_t[]>(CRYPTO_BYTES);
                randombytes(initializationVector1.get(), CRYPTO_BYTES);
                memcpy_s(initializationVector2.get(), CRYPTO_BYTES, initializationVector1.get(), CRYPTO_BYTES);
                Message encryptedMessage = Cryptor::Encrypt(Cryptor::ToMessage(unbox_value<hstring>(connectButton().Content())), sharedKey, initializationVector1);
                hstring message = Cryptor::ToHString(Cryptor::Decrypt(encryptedMessage, sharedKey, initializationVector2));
                connectButton().Content(box_value(Cryptor::ToHString(Signer::DilithiumSign(encryptedMessage, dilithiumKeyPair.PrivateKey))));
            }
            else
            {
                connectButton().Content(box_value(L"NO"));
            }
        }
        else
        {
            connectButton().Content(box_value(L"CHECK🌈"));
        }
    }
}
