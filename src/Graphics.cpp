#include "Graphics.hpp"
#include <iostream>

Graphics::Graphics() : initialized(false)
{
}

Graphics::~Graphics()
{
    if (initialized)
    {
        shutdown();
    }
}

bool Graphics::initialize(const char *windowTitle)
{
    if (initialized)
    {
        std::cerr << "Graphics already initialized" << std::endl;
        return false;
    }

    // Initialize Raylib window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, windowTitle);

    // Set target FPS
    SetTargetFPS(60);

    // Create render target for native CHIP-8 resolution
    renderTarget = LoadRenderTexture(CHIP8_WIDTH, CHIP8_HEIGHT);

    initialized = true;
    std::cout << "Graphics initialized: " << SCREEN_WIDTH << "x" << SCREEN_HEIGHT << std::endl;
    return true;
}

void Graphics::shutdown()
{
    if (!initialized)
    {
        return;
    }

    UnloadRenderTexture(renderTarget);
    CloseWindow();
    initialized = false;
    std::cout << "Graphics shutdown" << std::endl;
}

bool Graphics::shouldClose() const
{
    bool should_close = WindowShouldClose();
    return should_close;
}

void Graphics::render(const std::uint8_t *displayBuffer)
{
    if (!initialized)
    {
        return;
    }

    // Render to native resolution target
    BeginTextureMode(renderTarget);
    ClearBackground(BLACK);

    for (int y = 0; y < CHIP8_HEIGHT; ++y)
    {
        for (int x = 0; x < CHIP8_WIDTH; ++x)
        {
            if (displayBuffer[y * CHIP8_WIDTH + x] != 0)
            {
                DrawPixel(x, y, WHITE);
            }
        }
    }

    EndTextureMode();

    // Draw scaled to window
    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexturePro(
        renderTarget.texture,
        {0.0f, 0.0f, static_cast<float>(renderTarget.texture.width),
         -static_cast<float>(renderTarget.texture.height)}, // Flip Y
        {0.0f, 0.0f, static_cast<float>(SCREEN_WIDTH),
         static_cast<float>(SCREEN_HEIGHT)},
        {0.0f, 0.0f},
        0.0f,
        WHITE);

    EndDrawing();
}

void Graphics::setTargetFPS(int fps)
{
    SetTargetFPS(fps);
}