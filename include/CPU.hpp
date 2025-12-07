#pragma once
#include <cstdint>
#include <array>

// Forward declaration
class Memory;

/**
 * @brief CHIP-8 CPU implementation
 *
 * Implements the CHIP-8 instruction set with:
 * - 16 general purpose 8-bit registers (V0-VF)
 * - 16-bit index register (I)
 * - 16-bit program counter (PC)
 * - 16-level stack for subroutines
 * - Delay and sound timers
 * - 64x32 monochrome display
 * - 16-key hexadecimal keypad
 */
class CPU
{
public:
    // Display constants
    static constexpr std::size_t DISPLAY_WIDTH = 64;
    static constexpr std::size_t DISPLAY_HEIGHT = 32;
    static constexpr std::size_t DISPLAY_SIZE = DISPLAY_WIDTH * DISPLAY_HEIGHT;

    // Keyboard constants
    static constexpr std::size_t KEY_COUNT = 16;

    /**
     * @brief Constructor
     * @param memory Pointer to memory instance
     */
    explicit CPU(Memory *memory);

    /**
     * @brief Destructor
     */
    ~CPU() = default;

    /**
     * @brief Execute one CPU cycle (fetch, decode, execute)
     */
    void emulateCycle();

    /**
     * @brief Update timers (should be called at 60Hz)
     */
    void updateTimers();

    /**
     * @brief Reset CPU to initial state
     */
    void reset();

    // Display access
    const std::array<std::uint8_t, DISPLAY_SIZE> &getDisplay() const { return display; }

    // Input access
    std::array<std::uint8_t, KEY_COUNT> &getKeys() { return keys; }
    const std::array<std::uint8_t, KEY_COUNT> &getKeys() const { return keys; }

    // Timer access (for debugging/sound)
    std::uint8_t getDelayTimer() const { return delayTimer; }

private:
    // CPU Registers
    std::uint16_t opcode;                   // Current instruction
    std::uint16_t indexRegister;            // Index register (I)
    std::uint16_t programCounter;           // Program counter (PC)
    std::array<std::uint8_t, 16> registers; // V0-VF registers

    // Timers
    std::uint8_t delayTimer; // Delay timer
    std::uint8_t soundTimer; // Sound timer (not used)

    // Stack
    std::array<std::uint16_t, 16> stack; // Call stack
    std::uint8_t stackPointer;           // Stack pointer

    // I/O
    std::array<std::uint8_t, DISPLAY_SIZE> display; // Display buffer
    std::array<std::uint8_t, KEY_COUNT> keys;       // Key states

    // Memory reference
    Memory *memory;

    // Opcode handlers
    void executeOpcode0(std::uint16_t opcode);
    void executeOpcode1(std::uint16_t opcode);
    void executeOpcode2(std::uint16_t opcode);
    void executeOpcode3(std::uint16_t opcode);
    void executeOpcode4(std::uint16_t opcode);
    void executeOpcode5(std::uint16_t opcode);
    void executeOpcode6(std::uint16_t opcode);
    void executeOpcode7(std::uint16_t opcode);
    void executeOpcode8(std::uint16_t opcode);
    void executeOpcode9(std::uint16_t opcode);
    void executeOpcodeA(std::uint16_t opcode);
    void executeOpcodeB(std::uint16_t opcode);
    void executeOpcodeC(std::uint16_t opcode);
    void executeOpcodeD(std::uint16_t opcode);
    void executeOpcodeE(std::uint16_t opcode);
    void executeOpcodeF(std::uint16_t opcode);

    // Helper functions
    std::uint8_t generateRandomByte();
    void clearDisplay();
    bool drawSprite(std::uint8_t x, std::uint8_t y, std::uint8_t height);
};