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

private:
    bool Init();

    SDL_Window* _window = nullptr;
    const std::string_view _title;
    const int _width = 800;
    const int _height = 600;

    bool _shouldBeClosed = false;
};