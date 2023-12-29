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
        spdlog::info(winrt::Windows::Storage::ApplicationData::Current().LocalFolder().Path());
        /*WSADATA wsaData;
        int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (result != 0)
        {
            spdlog::error("WSAStartup failed: [{}]", result);
        }
        clientSocket = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
        if (clientSocket == INVALID_SOCKET)
        {
            spdlog::error("socket failed: [{}]", WSAGetLastError());
            WSACleanup();
        }
        std::wstring strIp = L"::1";
        std::wstring strPort = L"5678";
        char ip[INET6_ADDRSTRLEN];
        size_t convertedChars = 0;
        wcstombs_s(&convertedChars, ip, INET6_ADDRSTRLEN, strIp.c_str(), strIp.length());
        struct sockaddr_in6 serverAddress;
        memset(&serverAddress, 0, sizeof(serverAddress));
        serverAddress.sin6_family = AF_INET6;
        serverAddress.sin6_port = htons(static_cast<unsigned short>(std::stoul(strPort)));
        inet_pton(AF_INET6, ip, &serverAddress.sin6_addr);
        result = connect(clientSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress));
        if (result == SOCKET_ERROR)
        {
            spdlog::error("connection failed: [{}]", WSAGetLastError());
            closesocket(clientSocket);
            WSACleanup();
        }*/
        //while (true)
        //{
        //    std::string msg = "hello";
        //    Message message;
        //    int bytesSent = send(clientSocket, reinterpret_cast<const char*>(message.Size), sizeof(size_t), 0);
        //    //StringMessage message3(msg);
        //    //Message<int32_t> message2(msg.size() * sizeof(wchar_t));
        //    bytesSent = send(clientSocket, msg.c_str(), sizeof(int32_t), 0);
        //    bytesSent = send(clientSocket, msg.c_str(), message2.GetData(), 0);
        //    msg.clear();
        //}
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
