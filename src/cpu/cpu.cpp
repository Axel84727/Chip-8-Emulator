#include "cpu.hpp"

cpu::cpu()
{
    opcode = 0;
    I = 0;
    delay = 0;
    pc = 0x200;
    sound_timers = 0;
    stack_pointer = 0;
    for (int i = 0; i < 16; ++i)
    {
        V[i] = 0;
        stack[i] = 0;
    }
}