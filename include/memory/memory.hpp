#pragma once
#include <cstdint>
#include <array>

class memory
{
public:
    // El tamaño de la memoria del CHIP-8 es de 4096 bytes (4KB)
    static constexpr int MEMORY_SIZE = 4096;

    // Constructor. Inicializa la memoria (y carga el Fontset).
    memory();
    ~memory() = default;

    // Métodos esenciales de acceso para la CPU
    std::uint8_t read_byte(std::uint16_t address) const;
    void write_byte(std::uint16_t address, std::uint8_t value);

    // Carga del programa (ROM) en memoria a partir de 0x200
    bool load_rom(const char *filename);

private:
    // El array de memoria. std::array es preferido sobre el C-array
    std::array<std::uint8_t, MEMORY_SIZE> total_memory;
};