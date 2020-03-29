#pragma once

#include <SDL.h>

struct Texture
{
public:
    Texture() = default;
    ~Texture();

    Texture(const Texture& other);

    Texture& operator=(const Texture& other);

    SDL_Texture* texture = nullptr;
    int width = 0;
    int height = 0;

private:
    void Free();
};
