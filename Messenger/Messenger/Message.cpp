#include "pch.h"

#include "Message.h"

Message::Message() noexcept
{

}

Message::Message(std::unique_ptr<uint8_t[]>&& data, size_t size) noexcept
{
	Data.swap(data);
	Size = size;
}

Message::Message(Message&& other) noexcept
{
	Data.swap(other.Data);
	Size = other.Size;
}
