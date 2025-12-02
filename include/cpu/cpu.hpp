#pragma once
#include <cstdint>

struct cpu
{
    std::uint16_t opcode;
    std::uint16_t I; // This register is generally used to store memory addresses
    std::uint8_t delay;
    std::uint16_t pc; // is used to store the currently executing address.
    std::uint8_t sound_timers;
    std::uint8_t stack_pointer; // it is used to point to the topmost level of the stack.
    std::uint8_t V[16];         // Chip-8 has 16 general purpose 8-bit registers, usually referred to as Vx
    std::uint16_t stack[16];

    cpu::cpu(
        std::uint16_t opcode,
        std::uint16_t I,
        std::uint8_t delay,
        std::uint16_t pc,
        std::uint8_t sound_timers,
        std::uint8_t stack_pointer);
};
