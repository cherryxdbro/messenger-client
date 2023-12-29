#pragma once

struct Message final
{
	Message() noexcept;
	Message(std::unique_ptr<uint8_t[]>&& data, size_t size) noexcept;
	Message(Message&& other) noexcept;

	std::unique_ptr<uint8_t[]> Data;
	size_t Size;
};
