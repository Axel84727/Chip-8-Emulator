#pragma once
#include <cstdint>
#include <cstddef>

/**
 * @brief Input handler for CHIP-8 emulator
 *
 * Maps keyboard input to CHIP-8 hexadecimal keypad:
 * CHIP-8 Keypad:    Keyboard Mapping:
 * 1 2 3 C    →      1 2 3 4
 * 4 5 6 D    →      Q W E R
 * 7 8 9 E    →      A S D F
 * A 0 B F    →      Z X C V
 */
class Input
{
public:
    static constexpr std::size_t KEY_COUNT = 16;

    /**
     * @brief Constructor
     */
    Input();

    /**
     * @brief Destructor
     */
    ~Input() = default;

    /**
     * @brief Update key states from keyboard input
     * @param keys Array to store key states (16 keys)
     */
    void updateKeys(std::uint8_t *keys);

    /**
     * @brief Check if a specific CHIP-8 key is pressed
     * @param key CHIP-8 key (0x0 to 0xF)
     * @return true if key is pressed
     */
    bool isKeyPressed(std::uint8_t key) const;

private:
    std::uint8_t keyStates[KEY_COUNT];
};