#include "CPU.hpp"
#include "Memory.hpp"
#include <cstring>
#include <cstdlib>
#include <iostream>

CPU::CPU(Memory *mem)
    : memory(mem)
{
    reset();
}

void CPU::reset()
{
    // Initialize CPU state
    opcode = 0;
    indexRegister = 0;
    programCounter = Memory::PROGRAM_START; // Start execution at 0x200

    // Clear registers
    registers.fill(0);

    // Clear timers
    delayTimer = 0;
    soundTimer = 0;

    // Clear stack
    stack.fill(0);
    stackPointer = 0;

    // Clear display and keys
    display.fill(0);
    keys.fill(0);
}

void CPU::updateTimers()
{
    if (delayTimer > 0)
    {
        delayTimer--;
    }

    // Sound timer is decremented but not used for actual sound
    if (soundTimer > 0)
    {
        soundTimer--;
    }
}

void CPU::emulateCycle()
{
    // Fetch instruction
    std::uint8_t highByte = memory->readByte(programCounter);
    std::uint8_t lowByte = memory->readByte(programCounter + 1);
    opcode = (highByte << 8) | lowByte;

    // Decode and execute instruction
    switch (opcode & 0xF000)
    {
    case 0x0000:
        executeOpcode0(opcode);
        break;
    case 0x1000:
        executeOpcode1(opcode);
        break;
    case 0x2000:
        executeOpcode2(opcode);
        break;
    case 0x3000:
        executeOpcode3(opcode);
        break;
    case 0x4000:
        executeOpcode4(opcode);
        break;
    case 0x5000:
        executeOpcode5(opcode);
        break;
    case 0x6000:
        executeOpcode6(opcode);
        break;
    case 0x7000:
        executeOpcode7(opcode);
        break;
    case 0x8000:
        executeOpcode8(opcode);
        break;
    case 0x9000:
        executeOpcode9(opcode);
        break;
    case 0xA000:
        executeOpcodeA(opcode);
        break;
    case 0xB000:
        executeOpcodeB(opcode);
        break;
    case 0xC000:
        executeOpcodeC(opcode);
        break;
    case 0xD000:
        executeOpcodeD(opcode);
        break;
    case 0xE000:
        executeOpcodeE(opcode);
        break;
    case 0xF000:
        executeOpcodeF(opcode);
        break;
    default:
        std::cerr << "Unknown opcode: 0x" << std::hex << opcode << std::endl;
        programCounter += 2;
        break;
    }
}

std::uint8_t CPU::generateRandomByte()
{
    return static_cast<std::uint8_t>(std::rand() % 256);
}

void CPU::clearDisplay()
{
    display.fill(0);
}

bool CPU::drawSprite(std::uint8_t x, std::uint8_t y, std::uint8_t height)
{
    bool collision = false;

    for (std::uint8_t row = 0; row < height; ++row)
    {
        std::uint8_t spriteData = memory->readByte(indexRegister + row);

        for (std::uint8_t col = 0; col < 8; ++col)
        {
            std::uint8_t spritePixel = (spriteData >> (7 - col)) & 1;

            if (spritePixel)
            {
                std::uint8_t pixelX = (x + col) % DISPLAY_WIDTH;
                std::uint8_t pixelY = (y + row) % DISPLAY_HEIGHT;
                std::size_t pixelIndex = pixelY * DISPLAY_WIDTH + pixelX;

                if (display[pixelIndex])
                {
                    collision = true;
                }
                display[pixelIndex] ^= 1;
            }
        }
    }

    return collision;
}

// Opcode 0x0XXX implementations
void CPU::executeOpcode0(std::uint16_t opcode)
{
    switch (opcode & 0x00FF)
    {
    case 0x00E0: // CLS - Clear display
        clearDisplay();
        programCounter += 2;
        break;

    case 0x00EE: // RET - Return from subroutine
        if (stackPointer > 0)
        {
            stackPointer--;
            programCounter = stack[stackPointer];
        }
        else
        {
            std::cerr << "Stack underflow!" << std::endl;
            programCounter += 2;
        }
        break;

    default:
        std::cerr << "Unknown 0x0XXX opcode: 0x" << std::hex << opcode << std::endl;
        programCounter += 2;
        break;
    }
}

// 0x1NNN - JP addr - Jump to address NNN
void CPU::executeOpcode1(std::uint16_t opcode)
{
    std::uint16_t address = opcode & 0x0FFF;
    programCounter = address;
}

// 0x2NNN - CALL addr - Call subroutine at NNN
void CPU::executeOpcode2(std::uint16_t opcode)
{
    if (stackPointer < stack.size())
    {
        stack[stackPointer] = programCounter + 2;
        stackPointer++;
        programCounter = opcode & 0x0FFF;
    }
    else
    {
        std::cerr << "Stack overflow!" << std::endl;
        programCounter += 2;
    }
}

// 0x3XNN - SE Vx, byte - Skip next instruction if Vx == NN
void CPU::executeOpcode3(std::uint16_t opcode)
{
    std::uint8_t regX = (opcode & 0x0F00) >> 8;
    std::uint8_t value = opcode & 0x00FF;

    if (registers[regX] == value)
    {
        programCounter += 4;
    }
    else
    {
        programCounter += 2;
    }
}

// 0x4XNN - SNE Vx, byte - Skip next instruction if Vx != NN
void CPU::executeOpcode4(std::uint16_t opcode)
{
    std::uint8_t regX = (opcode & 0x0F00) >> 8;
    std::uint8_t value = opcode & 0x00FF;

    if (registers[regX] != value)
    {
        programCounter += 4;
    }
    else
    {
        programCounter += 2;
    }
}

// 0x5XY0 - SE Vx, Vy - Skip next instruction if Vx == Vy
void CPU::executeOpcode5(std::uint16_t opcode)
{
    std::uint8_t regX = (opcode & 0x0F00) >> 8;
    std::uint8_t regY = (opcode & 0x00F0) >> 4;

    if (registers[regX] == registers[regY])
    {
        programCounter += 4;
    }
    else
    {
        programCounter += 2;
    }
}

// 0x6XNN - LD Vx, byte - Set Vx = NN
void CPU::executeOpcode6(std::uint16_t opcode)
{
    std::uint8_t regX = (opcode & 0x0F00) >> 8;
    std::uint8_t value = opcode & 0x00FF;

    registers[regX] = value;
    programCounter += 2;
}

// 0x7XNN - ADD Vx, byte - Set Vx = Vx + NN
void CPU::executeOpcode7(std::uint16_t opcode)
{
    std::uint8_t regX = (opcode & 0x0F00) >> 8;
    std::uint8_t value = opcode & 0x00FF;

    registers[regX] += value;
    programCounter += 2;
}

// 0x8XYN - Arithmetic and logic operations
void CPU::executeOpcode8(std::uint16_t opcode)
{
    std::uint8_t regX = (opcode & 0x0F00) >> 8;
    std::uint8_t regY = (opcode & 0x00F0) >> 4;
    std::uint8_t operation = opcode & 0x000F;

    switch (operation)
    {
    case 0x0: // LD Vx, Vy - Set Vx = Vy
        registers[regX] = registers[regY];
        break;

    case 0x1: // OR Vx, Vy - Set Vx = Vx OR Vy
        registers[regX] |= registers[regY];
        break;

    case 0x2: // AND Vx, Vy - Set Vx = Vx AND Vy
        registers[regX] &= registers[regY];
        break;

    case 0x3: // XOR Vx, Vy - Set Vx = Vx XOR Vy
        registers[regX] ^= registers[regY];
        break;

    case 0x4: // ADD Vx, Vy - Set Vx = Vx + Vy, set VF = carry
    {
        std::uint16_t sum = registers[regX] + registers[regY];
        registers[0xF] = (sum > 255) ? 1 : 0;
        registers[regX] = static_cast<std::uint8_t>(sum);
    }
    break;

    case 0x5: // SUB Vx, Vy - Set Vx = Vx - Vy, set VF = NOT borrow
        registers[0xF] = (registers[regX] > registers[regY]) ? 1 : 0;
        registers[regX] -= registers[regY];
        break;

    case 0x6: // SHR Vx {, Vy} - Set Vx = Vx SHR 1
        registers[0xF] = registers[regX] & 0x1;
        registers[regX] >>= 1;
        break;

    case 0x7: // SUBN Vx, Vy - Set Vx = Vy - Vx, set VF = NOT borrow
        registers[0xF] = (registers[regY] > registers[regX]) ? 1 : 0;
        registers[regX] = registers[regY] - registers[regX];
        break;

    case 0xE: // SHL Vx {, Vy} - Set Vx = Vx SHL 1
        registers[0xF] = (registers[regX] & 0x80) >> 7;
        registers[regX] <<= 1;
        break;

    default:
        std::cerr << "Unknown 0x8XXX opcode: 0x" << std::hex << opcode << std::endl;
        break;
    }

    programCounter += 2;
}

// 0x9XY0 - SNE Vx, Vy - Skip next instruction if Vx != Vy
void CPU::executeOpcode9(std::uint16_t opcode)
{
    std::uint8_t regX = (opcode & 0x0F00) >> 8;
    std::uint8_t regY = (opcode & 0x00F0) >> 4;

    if (registers[regX] != registers[regY])
    {
        programCounter += 4;
    }
    else
    {
        programCounter += 2;
    }
}

// 0xANNN - LD I, addr - Set I = NNN
void CPU::executeOpcodeA(std::uint16_t opcode)
{
    indexRegister = opcode & 0x0FFF;
    programCounter += 2;
}

// 0xBNNN - JP V0, addr - Jump to location NNN + V0
void CPU::executeOpcodeB(std::uint16_t opcode)
{
    std::uint16_t address = opcode & 0x0FFF;
    programCounter = address + registers[0];
}

// 0xCXNN - RND Vx, byte - Set Vx = random byte AND NN
void CPU::executeOpcodeC(std::uint16_t opcode)
{
    std::uint8_t regX = (opcode & 0x0F00) >> 8;
    std::uint8_t value = opcode & 0x00FF;

    registers[regX] = generateRandomByte() & value;
    programCounter += 2;
}

// 0xDXYN - DRW Vx, Vy, nibble - Display n-byte sprite starting at memory location I at (Vx, Vy)
void CPU::executeOpcodeD(std::uint16_t opcode)
{
    std::uint8_t regX = (opcode & 0x0F00) >> 8;
    std::uint8_t regY = (opcode & 0x00F0) >> 4;
    std::uint8_t height = opcode & 0x000F;

    bool collision = drawSprite(registers[regX], registers[regY], height);
    registers[0xF] = collision ? 1 : 0;

    programCounter += 2;
}

// 0xEXXX - Keyboard operations
void CPU::executeOpcodeE(std::uint16_t opcode)
{
    std::uint8_t regX = (opcode & 0x0F00) >> 8;
    std::uint8_t operation = opcode & 0x00FF;

    switch (operation)
    {
    case 0x9E: // SKP Vx - Skip next instruction if key with the value of Vx is pressed
        if (keys[registers[regX]])
        {
            programCounter += 4;
        }
        else
        {
            programCounter += 2;
        }
        break;

    case 0xA1: // SKNP Vx - Skip next instruction if key with the value of Vx is not pressed
        if (!keys[registers[regX]])
        {
            programCounter += 4;
        }
        else
        {
            programCounter += 2;
        }
        break;

    default:
        std::cerr << "Unknown 0xEXXX opcode: 0x" << std::hex << opcode << std::endl;
        programCounter += 2;
        break;
    }
}

// 0xFXXX - Timer and memory operations
void CPU::executeOpcodeF(std::uint16_t opcode)
{
    std::uint8_t regX = (opcode & 0x0F00) >> 8;
    std::uint8_t operation = opcode & 0x00FF;

    switch (operation)
    {
    case 0x07: // LD Vx, DT - Set Vx = delay timer value
        registers[regX] = delayTimer;
        break;

    case 0x0A: // LD Vx, K - Wait for a key press, store the value of the key in Vx
    {
        bool keyPressed = false;
        for (std::uint8_t i = 0; i < KEY_COUNT; ++i)
        {
            if (keys[i])
            {
                registers[regX] = i;
                keyPressed = true;
                break;
            }
        }
        if (!keyPressed)
        {
            return; // Don't increment PC, wait for key press
        }
    }
    break;

    case 0x15: // LD DT, Vx - Set delay timer = Vx
        delayTimer = registers[regX];
        break;

    case 0x18: // LD ST, Vx - Set sound timer = Vx (not used)
        soundTimer = registers[regX];
        break;

    case 0x1E: // ADD I, Vx - Set I = I + Vx
        indexRegister += registers[regX];
        break;

    case 0x29: // LD F, Vx - Set I = location of sprite for digit Vx
        indexRegister = Memory::FONT_START + (registers[regX] * 5);
        break;

    case 0x33: // LD B, Vx - Store BCD representation of Vx in memory locations I, I+1, and I+2
        memory->writeByte(indexRegister, registers[regX] / 100);
        memory->writeByte(indexRegister + 1, (registers[regX] / 10) % 10);
        memory->writeByte(indexRegister + 2, registers[regX] % 10);
        break;

    case 0x55: // LD [I], Vx - Store registers V0 through Vx in memory starting at location I
        for (std::uint8_t i = 0; i <= regX; ++i)
        {
            memory->writeByte(indexRegister + i, registers[i]);
        }
        break;

    case 0x65: // LD Vx, [I] - Read registers V0 through Vx from memory starting at location I
        for (std::uint8_t i = 0; i <= regX; ++i)
        {
            registers[i] = memory->readByte(indexRegister + i);
        }
        break;

    default:
        std::cerr << "Unknown 0xFXXX opcode: 0x" << std::hex << opcode << std::endl;
        break;
    }

    programCounter += 2;
}