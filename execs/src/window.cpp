#include "window.hpp"
#include "exception.hpp"

#include <iostream>
#include "SDL_image.h"

Window ::Window(const std::string title, int width, int height) :
    _title(title),
    _width(width),
    _height(height)
{
    _shouldBeClosed = !Init();
}

Window::~Window()
{
    SDL_DestroyRenderer(_renderer);
    _renderer = nullptr;
    SDL_DestroyWindow(_window);
    _window = nullptr;
    SDL_Quit();
    IMG_Quit();
}

bool Window::Init()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        throw Exception("SDL not initialized");
    }

    _window = SDL_CreateWindow(
        _title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, 0);

    if(_window == nullptr)
    {
        throw Exception("SDL failed to create window");
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

    if(_renderer == nullptr)
    {
        throw Exception("SDL failed to create renderer");
    }

    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags))
    {
        std::string error = IMG_GetError();
        throw Exception(error);
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

void Window::Clear() const
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
}

void Window::UpdateWindow() const
{
    SDL_RenderPresent(_renderer);
    Clear();
}

SDL_Renderer* Window::GetRenderer() const
{
    return _renderer;
}

void Window::KeepBoidInScreen(Boid& boid) const
{
    if(boid.position.X() > _width)
    {
        boid.SetPosition(Vector2D(0, boid.position.Y()));
    }
    else if(boid.position.X() < 0)
    {
        boid.SetPosition(Vector2D(_width, boid.position.Y()));
    }

    if(boid.position.Y() > _height)
    {
        boid.SetPosition(Vector2D(boid.position.X(), 0));
    }
    else if(boid.position.Y() < 0)
    {
        boid.SetPosition(Vector2D(boid.position.X(), _height));
    }
}
