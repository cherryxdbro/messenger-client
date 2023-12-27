#include "pch.h"

#include "Cryptor.h"

Message Cryptor::ToMessage(const winrt::hstring& message)
{
    size_t messageSize = message.size() * sizeof(wchar_t);
    std::unique_ptr<uint8_t[]> messageData = std::make_unique<uint8_t[]>(messageSize);
    memcpy_s(messageData.get(), messageSize, message.c_str(), messageSize);
    return { std::move(messageData), messageSize };
}

winrt::hstring Cryptor::ToHString(const Message& message)
{
    return { reinterpret_cast<const wchar_t*>(message.Data.get()), static_cast<winrt::hstring::size_type>(message.Size / sizeof(wchar_t)) };
}

Message Cryptor::Encrypt(const Message& message, const std::unique_ptr<uint8_t[]>& sharedKey, const std::unique_ptr<uint8_t[]>& initializationVector)
{
    BCRYPT_ALG_HANDLE algorithmHandle;
    BCRYPT_KEY_HANDLE keyHandle;
    if (!NT_SUCCESS(BCryptOpenAlgorithmProvider(&algorithmHandle, BCRYPT_AES_ALGORITHM, nullptr, 0)))
    {
        throw CryptorError("Error BCryptOpenAlgorithmProvider");
    }
    if (!NT_SUCCESS(BCryptGenerateSymmetricKey(algorithmHandle, &keyHandle, nullptr, 0, sharedKey.get(), CRYPTO_BYTES, 0)))
    {
        throw CryptorError("Error BCryptGenerateSymmetricKey");
    }
    ULONG encryptedMessageSize = 0;
    if (!NT_SUCCESS(BCryptEncrypt(keyHandle, message.Data.get(), static_cast<ULONG>(message.Size), nullptr, initializationVector.get(), CRYPTO_BYTES, nullptr, 0, &encryptedMessageSize, BCRYPT_BLOCK_PADDING)))
    {
        throw CryptorError("Error BCryptEncrypt");
    };
    std::unique_ptr<uint8_t[]> encryptedMessage = std::make_unique<uint8_t[]>(encryptedMessageSize);
    if (!NT_SUCCESS(BCryptEncrypt(keyHandle, message.Data.get(), static_cast<ULONG>(message.Size), nullptr, initializationVector.get(), CRYPTO_BYTES, encryptedMessage.get(), encryptedMessageSize, &encryptedMessageSize, BCRYPT_BLOCK_PADDING)))
    {
        throw CryptorError("Error BCryptEncrypt");
    };
    return { std::move(encryptedMessage), encryptedMessageSize };
}

Message Cryptor::Decrypt(const Message& encryptedMessage, const std::unique_ptr<uint8_t[]>& sharedKey, const std::unique_ptr<uint8_t[]>& initializationVector)
{
    BCRYPT_ALG_HANDLE algorithmHandle;
    BCRYPT_KEY_HANDLE keyHandle;
    if (!NT_SUCCESS(BCryptOpenAlgorithmProvider(&algorithmHandle, BCRYPT_AES_ALGORITHM, nullptr, 0)))
    {
        throw CryptorError("Error BCryptOpenAlgorithmProvider");
    }
    if (!NT_SUCCESS(BCryptGenerateSymmetricKey(algorithmHandle, &keyHandle, nullptr, 0, sharedKey.get(), CRYPTO_BYTES, 0)))
    {
        throw CryptorError("Error BCryptGenerateSymmetricKey");
    }
    ULONG messageSize = 0;
    if (!NT_SUCCESS(BCryptDecrypt(keyHandle, encryptedMessage.Data.get(), static_cast<ULONG>(encryptedMessage.Size), nullptr, initializationVector.get(), CRYPTO_BYTES, nullptr, 0, &messageSize, BCRYPT_BLOCK_PADDING)))
    {
        throw CryptorError("Error BCryptDecrypt");
    };
    std::unique_ptr<uint8_t[]> message = std::make_unique<uint8_t[]>(messageSize);
    if (!NT_SUCCESS(BCryptDecrypt(keyHandle, encryptedMessage.Data.get(), static_cast<ULONG>(encryptedMessage.Size), nullptr, initializationVector.get(), CRYPTO_BYTES, message.get(), messageSize, &messageSize, BCRYPT_BLOCK_PADDING)))
    {
        throw CryptorError("Error BCryptDecrypt");
    };
    return { std::move(message), messageSize };
}
