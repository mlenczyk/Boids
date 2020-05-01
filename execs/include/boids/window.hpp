#pragma once

#include <SDL.h>
#include "boid.hpp"
#include "texture.hpp"

namespace flocking_simulation
{
    class Window
    {
    public:
        Window(const std::string title, int width, int height);
        ~Window();

        void PollEvents();
        bool IsClosed() const;
        void UpdateWindow() const;
        void KeepBoidInScreen(Boid& boid) const;
        Texture LoadTexture(std::string texturePath) const;
        void Render(Boid& boid) const;

        SDL_Renderer* _renderer = nullptr;

    private:
        bool Init();
        void Clear() const;

        const std::string _title;
        const int _width;
        const int _height;

        bool _shouldBeClosed = false;
        SDL_Window* _window = nullptr;
    };
}