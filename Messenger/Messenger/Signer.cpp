#include "pch.h"

#include "Signer.h"

extern "C"
{
	#include "sign.h"
}

Signer::DilithiumKeyPair::DilithiumKeyPair() noexcept
{

}

Signer::DilithiumKeyPair::DilithiumKeyPair(std::unique_ptr<uint8_t[]>&& publicKey, std::unique_ptr<uint8_t[]>&& privateKey) noexcept
{
    PublicKey.swap(publicKey);
    PrivateKey.swap(privateKey);
}

Signer::DilithiumKeyPair::DilithiumKeyPair(DilithiumKeyPair&& other) noexcept
{
    PublicKey.swap(other.PublicKey);
    PrivateKey.swap(other.PrivateKey);
}

Signer::DilithiumKeyPair& Signer::DilithiumKeyPair::operator=(DilithiumKeyPair&& other) noexcept
{
    if (this != &other)
    {
        PublicKey.swap(other.PublicKey);
        PrivateKey.swap(other.PrivateKey);
    }
    return *this;
}

Signer::DilithiumKeyPair Signer::MakeDilithiumKeyPair()
{
    std::unique_ptr<uint8_t[]> publicKey(new uint8_t[CRYPTO_PUBLICKEYBYTES]);
    std::unique_ptr<uint8_t[]> privateKey(new uint8_t[CRYPTO_SECRETKEYBYTES]);
    if (crypto_sign_keypair(publicKey.get(), privateKey.get()) != 0)
    {
        throw SignerError("Error crypto_sign_keypair");
    }
    return { std::move(publicKey), std::move(privateKey) };
}

Message Signer::DilithiumSign(const Message& message, const std::unique_ptr<uint8_t[]>& privateKey)
{
    size_t signedMessageLength;
    std::unique_ptr<uint8_t[]> signedMessage = std::make_unique<uint8_t[]>(message.Size + CRYPTO_BYTES);
    if (crypto_sign(signedMessage.get(), &signedMessageLength, message.Data.get(), message.Size, privateKey.get()) != 0)
    {
        throw SignerError("Error crypto_sign");
    }
    return { std::move(signedMessage), signedMessageLength };
}

Message Signer::DilithiumSignOpen(const Message& signedMessage, const std::unique_ptr<uint8_t[]>& publicKey)
{
    size_t messageLength;
    std::unique_ptr<uint8_t[]> message = std::make_unique<uint8_t[]>(signedMessage.Size);
    if (crypto_sign_open(message.get(), &messageLength, signedMessage.Data.get(), signedMessage.Size, publicKey.get()) != 0)
    {
        throw SignerError("Error crypto_sign_open");
    }
    return { std::move(message), messageLength };
}
