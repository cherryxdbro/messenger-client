#pragma once

struct Message final
{
	std::unique_ptr<uint8_t[]> Data;
	size_t Size;

	Message() noexcept;
	Message(std::unique_ptr<uint8_t[]>&& data, size_t size) noexcept;
	Message(Message&& other) noexcept;
};
