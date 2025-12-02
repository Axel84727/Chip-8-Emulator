#include "cpu.hpp"

cpu::cpu(
    std::uint16_t opcode,
    std::uint16_t I,
    std::uint8_t delay,
    std::uint16_t pc,
    std::uint8_t sound_timers,
    std::uint8_t stack_pointer)
    : opcode(opcode),
      I(I),
      delay(delay),
      pc(pc),
      sound_timers(sound_timers),
      stack_pointer(stack_pointer)
{
    for (int i = 0; i < 16; ++i)
    {
        V[i] = 0;
        stack[i] = 0;
    }
}