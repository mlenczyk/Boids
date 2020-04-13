#pragma once

// #include <SDL.h>
#include <SDL.h>
#include "boid.hpp"
#include "texture.hpp"
#include "timer.hpp"

class Window
{
public:
    Window(const std::string title, int width, int height);
    ~Window();

    void PollEvents();
    bool IsClosed() const;
    void UpdateWindow() const;
    void KeepBoidInScreen(flocking_simulation::Boid& boid) const;
    Texture LoadTexture(std::string texturePath) const;
    void Render(flocking_simulation::Boid& boid) const;

    SDL_Renderer* _renderer = nullptr;

private:
    bool Init();
    void Clear() const;

    const std::string _title;
    const int _width;
    const int _height;

    bool _shouldBeClosed = false;
    SDL_Window* _window = nullptr;

    LTimer _timer = LTimer();
};