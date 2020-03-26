#include "window.h"
#include "exception.h"

#include <iostream>
#include <string_view>

using std::string_view;
using namespace std::literals::string_view_literals;

Window ::Window(const string_view title, int width, int height) :
    _title(title),
    _width(width),
    _height(height)
{
    if(!Init())
    {
        _shouldBeClosed = true;
    }
}

Window::~Window()
{
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

bool Window::Init()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        throw Exception("SDL not initialized"sv);
    }

    _window = SDL_CreateWindow(
        _title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, 0);

    if(_window == nullptr)
    {
        throw Exception("SDL failed to create window"sv);
    }

    return true;
}

bool Window::IsClosed() const
{
    return _shouldBeClosed;
}

void Window::PollEvents()
{
    SDL_Event event;

    if(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
            {
                _shouldBeClosed = true;
                break;
            }
            default:
            {
                break;
            }
        }
    }
}