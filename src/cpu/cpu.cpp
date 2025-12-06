#include "cpu/cpu.hpp"

cpu::cpu()
    : opcode(0),
      I(0),
      delay(0),
      pc(0x200),
      sound_timers(0),
      stack_pointer(0),
      V{0},
      stack{0}
{
}

cpu::~cpu()
{
}