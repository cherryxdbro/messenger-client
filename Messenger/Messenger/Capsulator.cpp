#include "pch.h"

#include "Capsulator.h"

extern "C"
{
	#include "kem.h"
}

Capsulator::KyberKeyPair::KyberKeyPair() noexcept
{

}

Capsulator::KyberKeyPair::KyberKeyPair(std::unique_ptr<uint8_t[]>&& publicKey, std::unique_ptr<uint8_t[]>&& privateKey) noexcept
{
    PublicKey.swap(publicKey);
    PrivateKey.swap(privateKey);
}

Capsulator::KyberKeyPair::KyberKeyPair(KyberKeyPair&& other) noexcept
{
    PublicKey.swap(other.PublicKey);
    PrivateKey.swap(other.PrivateKey);
}

Capsulator::KyberKeyPair& Capsulator::KyberKeyPair::operator=(KyberKeyPair&& other) noexcept
{
    if (this != &other)
    {
        PublicKey.swap(other.PublicKey);
        PrivateKey.swap(other.PrivateKey);
    }
    return *this;
}

Capsulator::KyberCapsulated::KyberCapsulated() noexcept
{

}

Capsulator::KyberCapsulated::KyberCapsulated(std::unique_ptr<uint8_t[]>&& cipherText, std::unique_ptr<uint8_t[]>&& sharedKey) noexcept
{
    CipherText.swap(cipherText);
    SharedKey.swap(sharedKey);
}

Capsulator::KyberCapsulated::KyberCapsulated(KyberCapsulated&& other) noexcept
{
    CipherText.swap(other.CipherText);
    SharedKey.swap(other.SharedKey);
}

Capsulator::KyberCapsulated& Capsulator::KyberCapsulated::operator=(KyberCapsulated&& other) noexcept
{
    if (this != &other)
    {
        CipherText.swap(other.CipherText);
        SharedKey.swap(other.SharedKey);
    }
    return *this;
}

Capsulator::KyberKeyPair Capsulator::MakeKyberKeyPair()
{
    std::unique_ptr<uint8_t[]> publicKey(new uint8_t[CRYPTO_PUBLICKEYBYTES]);
    std::unique_ptr<uint8_t[]> privateKey(new uint8_t[CRYPTO_SECRETKEYBYTES]);
    if (crypto_kem_keypair(publicKey.get(), privateKey.get()))
    {
        throw CapsulatorError("Error crypto_kem_keypair");
    }
    return { std::move(publicKey), std::move(privateKey) };
}

Capsulator::KyberCapsulated Capsulator::KyberEncapsulateKey(const std::unique_ptr<uint8_t[]>& publicKey)
{
    std::unique_ptr<uint8_t[]> cipherText(new uint8_t[CRYPTO_CIPHERTEXTBYTES]);
    std::unique_ptr<uint8_t[]> sharedKey(new uint8_t[CRYPTO_BYTES]);
    if (crypto_kem_enc(cipherText.get(), sharedKey.get(), publicKey.get()))
    {
        throw CapsulatorError("Error crypto_kem_enc");
    }
    return { std::move(cipherText), std::move(sharedKey) };
}

std::unique_ptr<uint8_t[]> Capsulator::KyberDecapsulateKey(const std::unique_ptr<uint8_t[]>& cipherText, const std::unique_ptr<uint8_t[]>& privateKey)
{
    std::unique_ptr<uint8_t[]> cipherTextCopy(new uint8_t[CRYPTO_CIPHERTEXTBYTES]);
    std::unique_ptr<uint8_t[]> sharedKey(new uint8_t[CRYPTO_BYTES]);
    memcpy_s(cipherTextCopy.get(), CRYPTO_CIPHERTEXTBYTES, cipherText.get(), CRYPTO_CIPHERTEXTBYTES);
    if (crypto_kem_dec(sharedKey.get(), cipherTextCopy.get(), privateKey.get()))
    {
        throw CapsulatorError("Error crypto_kem_dec");
    }
    return { std::move(sharedKey) };
}

bool Capsulator::KyberVerify(const std::unique_ptr<uint8_t[]>& sharedKey1, const std::unique_ptr<uint8_t[]>& sharedKey2)
{
    return memcmp(sharedKey1.get(), sharedKey2.get(), CRYPTO_BYTES) == 0;
}
