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

void Window::KeepBoidInScreen(Boid& boid) const
{
    if(boid.position.X() > _width)
    {
        boid.position = Vector2D(0, boid.position.Y());
    }
    else if(boid.position.X() < 0)
    {
        boid.position = Vector2D(_width, boid.position.Y());
    }

    if(boid.position.Y() > _height)
    {
        boid.position = Vector2D(boid.position.X(), 0);
    }
    else if(boid.position.Y() < 0)
    {
        boid.position = Vector2D(boid.position.X(), _height);
    }
}

Texture Window::LoadTexture(std::string texturePath) const
{
    Texture texture = {};
    SDL_Texture* newTexture = nullptr;

    SDL_Surface* loadedSurface = IMG_Load(texturePath.c_str());
    if(loadedSurface == nullptr)
    {
        throw Exception(
            "Unable to load texture " + texturePath + "! SDL_image Error: " + IMG_GetError() + "\n");
    }

    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

    newTexture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
    if(newTexture == nullptr)
    {
        throw Exception(
            "Unable to create texture from " + texturePath + "! SDL Error: " + SDL_GetError() +
            "%s\n");
    }

    texture.texture = newTexture;
    texture.width = loadedSurface->w;
    texture.height = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);

    return texture;
}

void Window::Render(Boid& boid) const
{
    SDL_Rect renderQuad = {static_cast<int>(boid.position.X()),
                           static_cast<int>(boid.position.Y()),
                           boid.GetTexture()->width,
                           boid.GetTexture()->height};

    if(boid.clip != nullptr)
    {
        renderQuad.w = boid.clip->w;
        renderQuad.h = boid.clip->h;
    }

    auto result = SDL_RenderCopyEx(
        _renderer, boid.GetTexture()->texture, boid.clip, &renderQuad, boid.angle, boid.center, boid.flip);
    if(result == -1)
    {
        throw Exception("Boid rendering failed. " + std::string{SDL_GetError()});
    }
}