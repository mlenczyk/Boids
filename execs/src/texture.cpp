#include <algorithm>
// #include <SDl.h>
#include <SDL.h>

#include "boids/texture.hpp"

Texture::~Texture()
{
    Free();
}

Texture::Texture(Texture&& other) noexcept :
    texture{other.texture}, width{other.width}, height{other.height}
{
    other.texture = nullptr;
}

Texture& Texture::operator=(Texture&& other) noexcept
{
    using std::swap;

    auto a = std::move(other);
    swap(texture, a.texture);
    swap(width, a.width);
    swap(height, a.height);
    return *this;
}

// Texture::Texture(const Texture& other)
//{
//    texture = other.texture;
//    width = other.width;
//    height = other.height;
//}

// Texture& Texture::operator=(const Texture& other)
//{
//    if(this != &other)
//    {
//        Free();
//        texture = other.texture;
//        width = other.width;
//        height = other.height;
//    }
//    return *this;
//}

void Texture::Free()
{
    if(texture != nullptr)
    {
        SDL_DestroyTexture(texture);
    }
    texture = nullptr;
    width = 0;
    height = 0;
}