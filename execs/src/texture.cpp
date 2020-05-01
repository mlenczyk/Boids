#include <algorithm>
#include <SDL.h>

#include "boids/texture.hpp"

namespace flocking_simulation
{
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
}