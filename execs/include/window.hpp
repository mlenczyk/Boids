#pragma once

#include <string_view>
#include <SDL.h>

class Window
{
public:
    Window(const std::string_view title, int width, int height);
    ~Window();

    void PollEvents();
    bool IsClosed() const;
    void Clear() const;
    void UpdateView() const;
    SDL_Renderer* GetRenderer() const;
    // void Window::DrawBoid(Boid* boid) const;

private:
    bool Init();

    const std::string_view _title;
    const int _width = 800;
    const int _height = 600;

    bool _shouldBeClosed = false;

    SDL_Window* _window = nullptr;
    SDL_Surface* _screenSurface = nullptr;
    SDL_Surface* _boidSurface = nullptr;

protected:
    SDL_Renderer* _renderer = nullptr;
};

extern Window window;