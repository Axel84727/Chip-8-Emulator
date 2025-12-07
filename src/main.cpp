/**
 * @file main.cpp
 * @brief CHIP-8 Emulator - Main application entry point
 *
 * This is a simple CHIP-8 emulator implementation featuring:
 * - Complete CHIP-8 instruction set
 * - 64x32 pixel display with scaling
 * - 16-key hexadecimal keypad input
 * - ROM loading capabilities
 * - No sound output (sound timer functionality removed)
 *
 * The emulator consists of:
 * - CPU: Handles instruction execution and timing
 * - Memory: Manages 4KB RAM and ROM loading
 * - Graphics: Renders 64x32 pixel display using Raylib
 * - Input: Handles 16-key hexadecimal keypad input
 */

#include "CPU.hpp"
#include "Memory.hpp"
#include "Graphics.hpp"
#include "Input.hpp"
#include <iostream>
#include <string>

/**
 * @class Emulator
 * @brief Main emulator class that coordinates all components
 */
class Emulator
{
private:
    static constexpr int CPU_CYCLES_PER_FRAME = 9; ///< CPU cycles to execute per frame (≈540Hz at 60FPS)

    Memory memory;     ///< Memory management system
    CPU cpu;           ///< Central processing unit
    Graphics graphics; ///< Graphics rendering system
    Input input;       ///< Input handling system

public:
    /**
     * @brief Initialize emulator components
     */
    Emulator() : cpu(&memory)
    {
        // Components are initialized in member initializer list
    }

    /**
     * @brief Load ROM file into memory
     * @param filename Path to the ROM file
     * @return true if ROM loaded successfully, false otherwise
     */
    bool loadROM(const std::string &filename)
    {
        if (!memory.loadROM(filename.c_str()))
        {
            std::cerr << "Error: Failed to load ROM: " << filename << std::endl;
            return false;
        }

        std::cout << "Successfully loaded ROM: " << filename << std::endl;
        return true;
    }

    /**
     * @brief Main emulation loop
     */
    void run()
    {
        std::cout << "Starting CHIP-8 Emulator..." << std::endl;
        std::cout << "Initializing graphics..." << std::endl;

        // Initialize graphics
        if (!graphics.initialize("CHIP-8 Emulator"))
        {
            std::cerr << "Failed to initialize graphics!" << std::endl;
            return;
        }

        std::cout << "Graphics initialized successfully." << std::endl;
        std::cout << "Controls:" << std::endl;
        std::cout << "  CHIP-8 Keypad    Keyboard" << std::endl;
        std::cout << "  1 2 3 C    ->    1 2 3 4" << std::endl;
        std::cout << "  4 5 6 D    ->    Q W E R" << std::endl;
        std::cout << "  7 8 9 E    ->    A S D F" << std::endl;
        std::cout << "  A 0 B F    ->    Z X C V" << std::endl;
        std::cout << std::endl;

        std::cout << "Entering main emulation loop..." << std::endl;
        int frame_count = 0;

        // Main emulation loop
        while (!graphics.shouldClose())
        {
            frame_count++;
            if (frame_count % 300 == 0) // Print every 5 seconds at 60 FPS
            {
                std::cout << "Emulator running... Frame: " << frame_count << std::endl;
            }
            // Execute multiple CPU cycles per frame for proper speed
            for (int i = 0; i < CPU_CYCLES_PER_FRAME; i++)
            {
                cpu.emulateCycle();
            }

            // Update timers at 60Hz (once per frame)
            cpu.updateTimers();

            // Handle input
            auto &cpuKeys = cpu.getKeys();
            input.updateKeys(cpuKeys.data());

            // Render display
            graphics.render(cpu.getDisplay().data());
        }

        std::cout << "Emulator shutting down..." << std::endl;
    }
};

/**
 * @brief Main application entry point
 * @param argc Number of command line arguments
 * @param argv Array of command line arguments
 * @return 0 on success, 1 on error
 */
int main(int argc, char *argv[])
{
    // Check command line arguments
    if (argc != 2)
    {
        std::cout << "CHIP-8 Emulator" << std::endl;
        std::cout << "Usage: " << argv[0] << " <ROM_FILE>" << std::endl;
        std::cout << "Example: " << argv[0] << " games/pong.ch8" << std::endl;
        return 1;
    }

    try
    {
        // Create emulator instance
        Emulator emulator;

        // Load ROM
        const std::string romPath = argv[1];
        if (!emulator.loadROM(romPath))
        {
            return 1;
        }

        // Run emulator
        emulator.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}