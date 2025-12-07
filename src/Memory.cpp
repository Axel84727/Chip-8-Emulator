#include "Memory.hpp"
#include <fstream>
#include <iostream>
#include <cstring>

// CHIP-8 font set - each character is 4x5 pixels
static constexpr std::uint8_t FONT_SET[80] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

Memory::Memory()
{
    clear();
    loadFontSet();
}

std::uint8_t Memory::readByte(std::uint16_t address) const
{
    if (address >= MEMORY_SIZE)
    {
        std::cerr << "Memory read out of bounds: 0x" << std::hex << address << std::endl;
        return 0;
    }
    return ram[address];
}

void Memory::writeByte(std::uint16_t address, std::uint8_t value)
{
    if (address >= MEMORY_SIZE)
    {
        std::cerr << "Memory write out of bounds: 0x" << std::hex << address << std::endl;
        return;
    }
    ram[address] = value;
}

bool Memory::loadROM(const char *filename)
{
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open ROM file: " << filename << std::endl;
        return false;
    }

    // Get file size
    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Check if ROM fits in available memory space
    const std::streamsize maxRomSize = MEMORY_SIZE - PROGRAM_START;
    if (fileSize > maxRomSize)
    {
        std::cerr << "Error: ROM too large. Max size: " << maxRomSize
                  << " bytes, file size: " << fileSize << " bytes" << std::endl;
        file.close();
        return false;
    }

    // Load ROM into memory starting at PROGRAM_START
    if (!file.read(reinterpret_cast<char *>(&ram[PROGRAM_START]), fileSize))
    {
        std::cerr << "Error: Failed to read ROM file" << std::endl;
        file.close();
        return false;
    }

    file.close();
    std::cout << "ROM loaded successfully: " << filename
              << " (" << fileSize << " bytes)" << std::endl;
    return true;
}

void Memory::clear()
{
    ram.fill(0);
}

void Memory::loadFontSet()
{
    // Load font set into memory starting at FONT_START
    for (std::size_t i = 0; i < sizeof(FONT_SET); ++i)
    {
        ram[FONT_START + i] = FONT_SET[i];
    }
}