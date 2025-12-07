#pragma once
#include <cstdint>
#include "memory.hpp" // To use the memory class

class cpu
{
private:
    // 1. CPU components
    std::uint16_t opcode; // Current instruction (16-bit)
    std::uint16_t I;      // Index register (16-bit)
    std::uint16_t pc;     // Program counter (16-bit). Initialized to 0x200
    std::uint8_t V[16];   // General-purpose registers (V0 to VF)

    // 2. Timers
    std::uint8_t delay_timer; // Delay timer
    std::uint8_t sound_timer; // Sound timer

    // 3. Stack
    std::uint16_t stack[16];    // Stack for return addresses
    std::uint8_t stack_pointer; // Stack pointer

    // 4. Connection to Memory
    memory *memory_ptr; // Pointer to the memory instance

public:
    // Constructor that accepts a pointer to memory
    cpu(memory *mem_ptr);
    ~cpu() = default;

    void emulate_cycle();
};