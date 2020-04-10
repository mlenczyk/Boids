#pragma once

#include <SDL.h>

struct Texture
{
public:
    Texture() = default;
    ~Texture();

    Texture(const Texture& other) = delete;
    Texture(Texture&& other) noexcept;

    Texture& operator=(const Texture& other) = delete;
    Texture& operator=(Texture&& other) noexcept;

    SDL_Texture* texture = nullptr;
    int width = 0;
    int height = 0;

private:
    void Free();
};
