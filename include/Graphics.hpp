#pragma once
#include "raylib.h"
#include <cstdint>

/**
 * @brief Graphics renderer for CHIP-8 emulator
 *
 * Handles rendering the CHIP-8 display buffer to screen using Raylib.
 * Scales the native 64x32 resolution to a larger window size.
 */
class Graphics
{
public:
    static constexpr int CHIP8_WIDTH = 64;
    static constexpr int CHIP8_HEIGHT = 32;
    static constexpr int SCALE_FACTOR = 10;
    static constexpr int SCREEN_WIDTH = CHIP8_WIDTH * SCALE_FACTOR;
    static constexpr int SCREEN_HEIGHT = CHIP8_HEIGHT * SCALE_FACTOR;

    /**
     * @brief Constructor
     */
    Graphics();

    /**
     * @brief Destructor
     */
    ~Graphics();

    /**
     * @brief Initialize graphics system
     * @param windowTitle Window title
     * @return true if successful
     */
    bool initialize(const char *windowTitle);

    /**
     * @brief Shutdown graphics system
     */
    void shutdown();

    /**
     * @brief Check if window should close
     * @return true if window should close
     */
    bool shouldClose() const;

    /**
     * @brief Render the display buffer to screen
     * @param displayBuffer CHIP-8 display buffer (64x32 pixels)
     */
    void render(const std::uint8_t *displayBuffer);

    /**
     * @brief Set target FPS
     * @param fps Target frames per second
     */
    void setTargetFPS(int fps);

private:
    RenderTexture2D renderTarget;
    bool initialized;
};