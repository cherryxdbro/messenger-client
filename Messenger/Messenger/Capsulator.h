#pragma once

struct Capsulator final
{
	struct KyberKeyPair final
	{
		std::unique_ptr<uint8_t[]> PublicKey;
		std::unique_ptr<uint8_t[]> PrivateKey;

		KyberKeyPair() noexcept;
		KyberKeyPair(std::unique_ptr<uint8_t[]>&& publicKey, std::unique_ptr<uint8_t[]>&& privateKey) noexcept;
		KyberKeyPair(KyberKeyPair&& other) noexcept;

		KyberKeyPair& operator=(KyberKeyPair&& other) noexcept;
	};

	struct KyberCapsulated final
	{
		std::unique_ptr<uint8_t[]> CipherText;
		std::unique_ptr<uint8_t[]> SharedKey;

		KyberCapsulated() noexcept;
		KyberCapsulated(std::unique_ptr<uint8_t[]>&& cipherText, std::unique_ptr<uint8_t[]>&& sharedKey) noexcept;
		KyberCapsulated(KyberCapsulated&& other) noexcept;

		KyberCapsulated& operator=(KyberCapsulated&& other) noexcept;
	};

	struct CapsulatorError final : public std::runtime_error
	{
	public:
		using std::runtime_error::runtime_error;
	};

	static KyberKeyPair MakeKyberKeyPair();

	static KyberCapsulated KyberEncapsulateKey(const std::unique_ptr<uint8_t[]>& publicKey);
	static std::unique_ptr<uint8_t[]> KyberDecapsulateKey(const std::unique_ptr<uint8_t[]>& cipherText, const std::unique_ptr<uint8_t[]>& privateKey);

	static bool KyberVerify(const std::unique_ptr<uint8_t[]>& sharedKey1, const std::unique_ptr<uint8_t[]>& sharedKey2);
};
