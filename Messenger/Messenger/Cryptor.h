#pragma once

#include "Message.h"

#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)

constexpr auto CRYPTO_BYTES = 32;

struct Cryptor final
{
	struct CryptorError final : public std::runtime_error
	{
	public:
		using std::runtime_error::runtime_error;
	};

	static Message ToMessage(const winrt::hstring& message);
	static winrt::hstring ToHString(const Message& message);

	static Message Encrypt(const Message& message, const std::unique_ptr<uint8_t[]>& sharedKey, const std::unique_ptr<uint8_t[]>& initializationVector);
	static Message Decrypt(const Message& message, const std::unique_ptr<uint8_t[]>& sharedKey, const std::unique_ptr<uint8_t[]>& initializationVector);
};
