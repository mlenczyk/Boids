#include "window.hpp"
#include "exception.hpp"

#include <iostream>
#include "SDL_image.h"

Window ::Window(const std::string title, int width, int height) :
    _title(title), _width(width), _height(height)
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

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);
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
    static SDL_Event event;

    if(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
            {
                _shouldBeClosed = true;
                break;
            }
            case SDL_KEYDOWN:
            { // Start/stop
                if(event.key.keysym.sym == SDLK_s)
                {
                    if(_timer.isStarted())
                    {
                        _timer.stop();
                    }
                    else
                    {
                        _timer.start();
                    }
                }
                // Pause/unpause
                else if(event.key.keysym.sym == SDLK_p)
                {
                    if(_timer.isPaused())
                    {
                        _timer.unpause();
                    }
                    else
                    {
                        _timer.pause();
                    }
                }
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
    SDL_SetRenderDrawColor(_renderer, 0, 100, 250, 255);
    SDL_RenderDrawLine(_renderer, _width / 2, 0, _width / 2, _height);
    SDL_RenderDrawLine(_renderer, 0, _height / 2, _width, _height / 2);

    SDL_RenderPresent(_renderer);
    Clear();
}

void Window::KeepBoidInScreen(Boid& boid) const
{
    if(boid.position.X() > _width - 20)
    {
        boid.position = Vector2D(20, boid.position.Y());
    }
    else if(boid.position.X() < 20)
    {
        boid.position = Vector2D(_width - 20, boid.position.Y());
    }

    if(boid.position.Y() > _height - 20)
    {
        boid.position = Vector2D(boid.position.X(), 20);
    }
    else if(boid.position.Y() < 20)
    {
        boid.position = Vector2D(boid.position.X(), _height - 20);
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

    // SDL_FreeSurface(loadedSurface);

    return texture;
}

void Window::Render(Boid& boid) const
{
    SDL_Rect renderQuad = {static_cast<int>(boid.position.X()) - (boid.GetTexture()->width / 2),
                           static_cast<int>(boid.position.Y()) - ((boid.GetTexture()->height * 5) / 6),
                           boid.GetTexture()->width,
                           boid.GetTexture()->height};
    // is not drawn in the middle of texture.. bgug
    // boid.clip = renderQuad;

    boid.center.x = boid.GetTexture()->width / 2;
    boid.center.y = (boid.GetTexture()->height * 5) / 6;
    //&(boid.clip)
    auto result = SDL_RenderCopyEx(
        _renderer, boid.GetTexture()->texture, nullptr, &renderQuad, boid.angle, &(boid.center), boid.flip);
    // fix this shit
    // if(result == -1)
    //{
    //  throw Exception("Boid rendering failed. " + std::string{SDL_GetError()});
    //}
}
