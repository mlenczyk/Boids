#include <SDl.h>

#include "texture.hpp"

Texture::~Texture()
{
    Free();
}

Texture::Texture(const Texture& other)
{
    texture = other.texture;
    width = other.width;
    height = other.height;
}

Texture& Texture::operator=(const Texture& other)
{
    if(this != &other)
    {
        Free();
        texture = other.texture;
        width = other.width;
        height = other.height;
    }
    return *this;
}

void Texture::Free()
{
    SDL_DestroyTexture(texture);
    texture = nullptr;
    width = 0;
    height = 0;
}