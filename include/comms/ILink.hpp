#pragma once

#include <cstdint>
#include <cstddef>

class ILink
{
public:
    virtual ~ILink() = default;
    virtual void begin() = 0;
    virtual bool isUp() const = 0;
    virtual void send(const uint8_t* msg, std::size_t len) = 0;
    virtual std::size_t receive(uint8_t* buf, std::size_t maxLen) = 0; //
};