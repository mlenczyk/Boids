#include "window.hpp"
#include "exception.hpp"

#include <iostream>
#include <string_view>
#include "SDL_image.h"

using std::string_view;
using namespace std::literals::string_view_literals;

Window ::Window(const string_view title, int width, int height) :
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
    SDL_FreeSurface(_boidSurface);
    _boidSurface = nullptr;
    SDL_DestroyWindow(_window);
    _window = nullptr;
    SDL_Quit();
    IMG_Quit();
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

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

    if(_renderer == nullptr)
    {
        throw Exception("SDL failed to create renderer"sv);
    }

    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags))
    {
        std::string_view errorView{IMG_GetError()};
        throw Exception(errorView);
    }

    return true;
}

// bool Window::LoadMedia()
// {
//     // Loading success flag
//     bool success = true;

//     // Load PNG texture
//     gTexture = loadTexture("07_texture_loading_and_rendering/texture.png");
//     if(gTexture == NULL)
//     {
//         printf("Failed to load texture image!\n");
//         success = false;
//     }

//     return success;
// }

bool Window::IsClosed() const
{
    return _shouldBeClosed;
}

// void Window::DrawBoid(Boid* boid) const
// {
//     // // Set rendering space and render to screen
//     // SDL_Rect renderQuad = {boid->GetPosition().X(), boid->GetPosition().Y(), 10, 20};

//     // // Set clip rendering dimensions
//     // if(boid->clip != NULL)
//     // {
//     //     renderQuad.w = boid->clip->w;
//     //     renderQuad.h = boid->clip->h;
//     // }

//     // // Render to screen
//     // SDL_RenderCopyEx(_renderer, boid->tex, boid->clip, &renderQuad, boid->angle, boid->center, boid->flip);

//     SDL_Rect renderQuad = {boid->GetPosition().X(), boid->GetPosition().Y(), 10, 20};
//     SDL_RenderCopy(_renderer, boid->_texture, NULL, &renderQuad);
// }

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

void Window::UpdateView() const
{
    // SDL_UpdateWindowSurface(_window);
}

SDL_Renderer* Window::GetRenderer() const
{
    return _renderer;
}
