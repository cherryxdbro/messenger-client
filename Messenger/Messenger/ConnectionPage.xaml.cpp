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

namespace winrt::Messenger::implementation
{
    Capsulator::KyberKeyPair ConnectionPage::kyberKeyPair = Capsulator::MakeKyberKeyPair();
    Signer::DilithiumKeyPair ConnectionPage::dilithiumKeyPair = Signer::MakeDilithiumKeyPair();
    Message ConnectionPage::kyberSecretKeyServer;
    Message ConnectionPage::dilithiumPublicKeyServer;

    ConnectionPage::ConnectionPage()
    {
        InitializeComponent();
    }

    void ConnectionPage::connectButton_Click(Windows::Foundation::IInspectable const&, RoutedEventArgs const&)
    {
        WSADATA wsaData;
        int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (result != 0)
        {
            return;
        }
        clientSocket = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
        if (clientSocket == INVALID_SOCKET)
        {
            WSACleanup();
            return;
        }
        std::wstring strIp = ipTextBox().Text().c_str();
        char ip[INET6_ADDRSTRLEN];
        size_t convertedChars = 0;
        wcstombs_s(&convertedChars, ip, INET6_ADDRSTRLEN, strIp.c_str(), strIp.length());
        struct sockaddr_in6 serverAddress;
        memset(&serverAddress, 0, sizeof(serverAddress));
        serverAddress.sin6_family = AF_INET6;
        serverAddress.sin6_port = htons(static_cast<unsigned short>(std::stoul(portTextBox().Text().c_str())));
        inet_pton(AF_INET6, ip, &serverAddress.sin6_addr);
        result = connect(clientSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress));
        if (result == SOCKET_ERROR)
        {
            closesocket(clientSocket);
            WSACleanup();
            return;
        }
    }

    void ConnectionPage::sendDataButton_Click(Windows::Foundation::IInspectable const&, RoutedEventArgs const&)
    {
        rapidjson::Value value;
        rapidjson::Document document;
        document.SetObject();
        value.SetString(reinterpret_cast<const char*>(kyberKeyPair.PublicKey.data()), kyberKeyPair.PublicKey.size());
        document.AddMember("kyber_pk", value, document.GetAllocator());
        value.SetString(reinterpret_cast<const char*>(dilithiumKeyPair.PublicKey.data()), dilithiumKeyPair.PublicKey.size());
        document.AddMember("dilithium_pk", value, document.GetAllocator());
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        const char* message = buffer.GetString();
        int bytesSend = send(clientSocket, message, strlen(message), 0);
        /*if (unbox_value<hstring>(connectButton().Content()) != L"CHECK🌈")
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
        }*/
    }
}
