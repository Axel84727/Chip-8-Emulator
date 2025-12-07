# CHIP-8 Emulator

A modern C++ implementation of the CHIP-8 virtual machine, built with clean architecture and modular design. This emulator accurately recreates the behavior of the original CHIP-8 system from the 1970s.

## Features

- Complete CHIP-8 instruction set implementation
- 64x32 pixel monochrome display with configurable scaling
- 16-key hexadecimal keypad support
- 4KB memory management
- Delay and sound timer emulation
- Raylib-based graphics rendering
- Cross-platform compatibility (macOS, Linux, Windows)

## System Requirements

### Dependencies

- C++17 compatible compiler (GCC, Clang, or MSVC)
- CMake 3.16 or higher
- Raylib graphics library

### Installing Raylib

**macOS (using Homebrew):**

```bash
brew install raylib
```

**Linux (Ubuntu/Debian):**

```bash
sudo apt-get install libraylib-dev
```

**Windows:**
Follow the official Raylib installation guide at https://github.com/raysan5/raylib

## Building

1. Clone the repository:

```bash
git clone https://github.com/Axel84727/Chip-8-Emulator.git
cd Chip-8-Emulator
```

2. Create and navigate to build directory:

```bash
mkdir build && cd build
```

3. Configure and build with CMake:

```bash
cmake ..
make
```

4. The executable will be created at `build/bin/chip_8_emulator`

## Usage

### Running ROMs

```bash
./bin/chip_8_emulator <rom_file>
```

Example:

```bash
./bin/chip_8_emulator games/pong.ch8
./bin/chip_8_emulator roms/tetris.ch8
```

### Controls

The CHIP-8 keypad is mapped to your keyboard as follows:

```
CHIP-8 Keypad        Keyboard Mapping
1 2 3 C              1 2 3 4
4 5 6 D       ->     Q W E R
7 8 9 E              A S D F
A 0 B F              Z X C V
```

- **ESC**: Exit emulator
- Window can be closed normally through OS controls

## Architecture

The emulator is built with a modular architecture consisting of four main components:

### CPU (Central Processing Unit)

- **File**: `src/CPU.cpp`, `include/CPU.hpp`
- **Purpose**: Handles instruction fetching, decoding, and execution
- **Features**: Complete CHIP-8 instruction set, registers, timers, stack

### Memory

- **File**: `src/Memory.cpp`, `include/Memory.hpp`
- **Purpose**: Manages 4KB system memory and ROM loading
- **Features**: Memory read/write operations, ROM file loading, bounds checking

### Graphics

- **File**: `src/Graphics.cpp`, `include/Graphics.hpp`
- **Purpose**: Handles display rendering and window management
- **Features**: 64x32 pixel display, configurable scaling, Raylib integration

### Input

- **File**: `src/Input.cpp`, `include/Input.hpp`
- **Purpose**: Manages keyboard input and keypad state
- **Features**: Real-time key state tracking, CHIP-8 keypad mapping

## Technical Specifications

### CHIP-8 System Characteristics

- **Memory**: 4KB (4096 bytes)
- **Display**: 64x32 pixels, monochrome
- **Registers**: 16 8-bit general-purpose registers (V0-VF)
- **Index Register**: 16-bit register (I)
- **Program Counter**: 16-bit register (PC)
- **Stack**: 16 levels of 16-bit values
- **Timers**: 8-bit delay timer and sound timer (60Hz)
- **Instruction Set**: 35 instructions, 2 bytes each

### Emulator Implementation Details

- **CPU Speed**: Configurable (default: ~540 Hz)
- **Timer Frequency**: 60 Hz (as per specification)
- **Display Refresh**: 60 FPS
- **Rendering**: Hardware-accelerated via Raylib
- **Input Polling**: Real-time keyboard state checking

## File Structure

```
chip-8-emulator/
├── CMakeLists.txt              # Build configuration
├── README.md                   # This file
├── include/                    # Header files
│   ├── CPU.hpp                 # CPU class definition
│   ├── Graphics.hpp            # Graphics class definition
│   ├── Input.hpp               # Input class definition
│   └── Memory.hpp              # Memory class definition
├── src/                        # Source files
│   ├── CPU.cpp                 # CPU implementation
│   ├── Graphics.cpp            # Graphics implementation
│   ├── Input.cpp               # Input implementation
│   ├── Memory.cpp              # Memory implementation
│   └── main.cpp                # Main program entry point
└── build/                      # Build output directory
    └── bin/chip_8_emulator     # Compiled executable
```

## ROM Compatibility

This emulator is compatible with standard CHIP-8 ROM files (.ch8 format). Popular games include:

- Pong
- Tetris
- Space Invaders
- Breakout
- Pac-Man variants

ROM files should be placed in the project directory or specify the full path when running.

## Development

### Adding New Features

The modular design makes it easy to extend functionality:

1. **CPU Enhancements**: Modify `CPU.cpp` for instruction set extensions
2. **Graphics Features**: Extend `Graphics.cpp` for display enhancements
3. **Input Methods**: Update `Input.cpp` for additional input devices
4. **Memory Management**: Enhance `Memory.cpp` for advanced memory features

### Debugging

The emulator includes basic error handling and bounds checking. For development:

1. Enable debug symbols: `cmake -DCMAKE_BUILD_TYPE=Debug ..`
2. Use debugger tools like GDB or LLDB
3. Add logging statements in individual modules as needed

## Contributing

1. Fork the repository
2. Create a feature branch: `git checkout -b feature-name`
3. Make your changes with appropriate tests
4. Ensure code follows the existing style
5. Submit a pull request with a clear description

## License

This project is open source. See the LICENSE file for details.

## References

- [CHIP-8 Technical Reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM)
- [CHIP-8 Wikipedia](https://en.wikipedia.org/wiki/CHIP-8)
- [Raylib Documentation](https://www.raylib.com/)

## Author

Created by Axel84727

## Acknowledgments

- Original CHIP-8 specification by Joseph Weisbecker
- Raylib graphics library by Ramon Santamaria
- CHIP-8 community for ROM preservation and documentation
