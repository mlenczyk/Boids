#pragma once

#include <SDL.h>
#include "boid.hpp"

class Window
{
public:
    Window(const std::string title, int width, int height);
    ~Window();

    void PollEvents();
    bool IsClosed() const;
    void Clear() const;
    void UpdateView() const;
    void UpdateWindow() const;
    void KeepBoidInScreen(Boid& boid) const;

    SDL_Renderer* GetRenderer() const;
    // void Window::DrawBoid(Boid* boid) const;

private:
    bool Init();

    const std::string _title;
    const int _width = 800;
    const int _height = 600;

    bool _shouldBeClosed = false;

    SDL_Window* _window = nullptr;

protected:
    SDL_Renderer* _renderer = nullptr;
};

extern Window window;