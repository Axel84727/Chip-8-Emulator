#include "Input.hpp"
#include "raylib.h"
#include <cstring>

Input::Input()
{
    std::memset(keyStates, 0, sizeof(keyStates));
}

void Input::updateKeys(std::uint8_t *keys)
{
    // Clear all keys first
    std::memset(keys, 0, KEY_COUNT);
    std::memset(keyStates, 0, sizeof(keyStates));

    // Map keyboard input to CHIP-8 keys
    // Row 1: 1 2 3 C
    if (IsKeyDown(KEY_ONE))
    {
        keys[0x1] = 1;
        keyStates[0x1] = 1;
    }
    if (IsKeyDown(KEY_TWO))
    {
        keys[0x2] = 1;
        keyStates[0x2] = 1;
    }
    if (IsKeyDown(KEY_THREE))
    {
        keys[0x3] = 1;
        keyStates[0x3] = 1;
    }
    if (IsKeyDown(KEY_FOUR))
    {
        keys[0xC] = 1;
        keyStates[0xC] = 1;
    }

    // Row 2: 4 5 6 D
    if (IsKeyDown(KEY_Q))
    {
        keys[0x4] = 1;
        keyStates[0x4] = 1;
    }
    if (IsKeyDown(KEY_W))
    {
        keys[0x5] = 1;
        keyStates[0x5] = 1;
    }
    if (IsKeyDown(KEY_E))
    {
        keys[0x6] = 1;
        keyStates[0x6] = 1;
    }
    if (IsKeyDown(KEY_R))
    {
        keys[0xD] = 1;
        keyStates[0xD] = 1;
    }

    // Row 3: 7 8 9 E
    if (IsKeyDown(KEY_A))
    {
        keys[0x7] = 1;
        keyStates[0x7] = 1;
    }
    if (IsKeyDown(KEY_S))
    {
        keys[0x8] = 1;
        keyStates[0x8] = 1;
    }
    if (IsKeyDown(KEY_D))
    {
        keys[0x9] = 1;
        keyStates[0x9] = 1;
    }
    if (IsKeyDown(KEY_F))
    {
        keys[0xE] = 1;
        keyStates[0xE] = 1;
    }

    // Row 4: A 0 B F
    if (IsKeyDown(KEY_Z))
    {
        keys[0xA] = 1;
        keyStates[0xA] = 1;
    }
    if (IsKeyDown(KEY_X))
    {
        keys[0x0] = 1;
        keyStates[0x0] = 1;
    }
    if (IsKeyDown(KEY_C))
    {
        keys[0xB] = 1;
        keyStates[0xB] = 1;
    }
    if (IsKeyDown(KEY_V))
    {
        keys[0xF] = 1;
        keyStates[0xF] = 1;
    }
}

bool Input::isKeyPressed(std::uint8_t key) const
{
    if (key >= KEY_COUNT)
    {
        return false;
    }
    return keyStates[key] != 0;
}