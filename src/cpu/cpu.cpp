#include "cpu.hpp"
#include <cstring> // For std::memset or std::fill

cpu::cpu(memory *mem_ptr)
    : opcode(0),
      I(0),
      pc(0x200), // Execution starts at 0x200
      delay_timer(0),
      sound_timer(0),
      stack_pointer(0),
      memory_ptr(mem_ptr) // Assign memory pointer
{
    // Initialize V registers and stack to zero
    std::memset(V, 0, sizeof(V));
    std::memset(stack, 0, sizeof(stack));
}

void cpu::emulate_cycle()
{
    // 1. FETCH (Get Opcode)
    std::uint16_t byte1 = memory_ptr->read_byte(pc);
    std::uint16_t byte2 = memory_ptr->read_byte(pc + 1);

    opcode = (byte1 << 8) | byte2; // Big-Endian: MSB + LSB

    switch (opcode & 0xF000)
    {
    case 0x1000:
        }
}