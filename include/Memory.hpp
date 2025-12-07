#pragma once
#include <cstdint>
#include <array>

/**
 * @brief Memory management class for CHIP-8 emulator
 *
 * Handles the 4KB memory space of the CHIP-8 system, including:
 * - Font data (0x50-0x9F)
 * - Program data (0x200-0xFFF)
 * - Provides read/write operations with bounds checking
 */
class Memory
{
public:
    static constexpr std::size_t MEMORY_SIZE = 4096;      // 4KB total memory
    static constexpr std::uint16_t FONT_START = 0x50;     // Font data starts here
    static constexpr std::uint16_t PROGRAM_START = 0x200; // Programs start here

    /**
     * @brief Constructor - initializes memory and loads font data
     */
    Memory();

    /**
     * @brief Destructor
     */
    ~Memory() = default;

    /**
     * @brief Read a byte from memory
     * @param address Memory address to read from
     * @return Byte value at the specified address
     */
    std::uint8_t readByte(std::uint16_t address) const;

    /**
     * @brief Write a byte to memory
     * @param address Memory address to write to
     * @param value Byte value to write
     */
    void writeByte(std::uint16_t address, std::uint8_t value);

    /**
     * @brief Load ROM file into memory starting at PROGRAM_START
     * @param filename Path to the ROM file
     * @return true if successful, false otherwise
     */
    bool loadROM(const char *filename);

    /**
     * @brief Clear all memory
     */
    void clear();

private:
    std::array<std::uint8_t, MEMORY_SIZE> ram;

    /**
     * @brief Load font set into memory
     */
    void loadFontSet();
};