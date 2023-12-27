#pragma once

#include "Message.h"

struct Signer final
{
	struct DilithiumKeyPair final
	{
		std::unique_ptr<uint8_t[]> PublicKey;
		std::unique_ptr<uint8_t[]> PrivateKey;

		DilithiumKeyPair() noexcept;
		DilithiumKeyPair(std::unique_ptr<uint8_t[]>&& publicKey, std::unique_ptr<uint8_t[]>&& privateKey) noexcept;
		DilithiumKeyPair(DilithiumKeyPair&& other) noexcept;

		DilithiumKeyPair& operator=(DilithiumKeyPair&& other) noexcept;
	};

	struct SignerError final : public std::runtime_error
	{
	public:
		using std::runtime_error::runtime_error;
	};

	static DilithiumKeyPair MakeDilithiumKeyPair();

	static Message DilithiumSign(const Message& message, const std::unique_ptr<uint8_t[]>& privateKey);
	static Message DilithiumSignOpen(const Message& signedMessage, const std::unique_ptr<uint8_t[]>& publicKey);
};
