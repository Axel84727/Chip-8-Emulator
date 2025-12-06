#pragma once
#include <cstdint>

class cpu
{
private:
    std::uint16_t opcode;
    std::uint16_t I;
    std::uint8_t delay;
    std::uint16_t pc;
    std::uint8_t sound_timers;
    std::uint8_t stack_pointer;
    std::uint8_t V[16];
    std::uint16_t stack[16];

public:
    cpu();
    ~cpu();
};