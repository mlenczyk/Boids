#include "boids/window.hpp"
#include "boids/boid.hpp"
#include "boids/exception.hpp"
#include "boids/vector2d.hpp"

#include <iostream>
#include "SDL_image.h"

namespace flocking_simulation
{
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
                case SDL_MOUSEBUTTONDOWN:
                {
                    int mousePosX;
                    int mousePosY;

                    SDL_GetMouseState(&mousePosX, &mousePosY);

                    if(event.button.button == SDL_BUTTON_LEFT)
                    {
                        AddObstaclePoint(mousePosX, mousePosY);
                    }

                    if(event.button.button == SDL_BUTTON_RIGHT)
                    {
                        DeleteObstaclePoint(mousePosX, mousePosY);
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

    void Window::AddObstaclePoint(int x, int y)
    {
        _obstacles.push_back(SDL_Point{x, y});
    }

    void Window::DeleteObstaclePoint(int x, int y)
    {
        static constexpr int precision = 10;

        _obstacles.erase(
            std::remove_if(
                _obstacles.begin(),
                _obstacles.end(),
                [&](const SDL_Point& point) {
                    return (
                        ((x - precision) <= point.x && point.x <= (x + precision)) &&
                        ((y - precision) <= point.y && point.y <= (y + precision)));
                }),
            _obstacles.end());
    }

    void Window::DrawPoints(const std::vector<SDL_Point>& points)
    {
        SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

        SDL_RenderDrawPoints(_renderer, points.data(), points.size());
    }

    void Window::Clear() const
    {
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
        SDL_RenderClear(_renderer);
    }

    void Window::UpdateWindow()
    {
        DrawPoints(_obstacles);
        SDL_RenderPresent(_renderer);
        Clear();
    }

    void Window::KeepBoidInScreen(Boid& boid) const
    {
        if(boid.position.X() > _width - 1)
        {
            boid.position = Vector2D(1, boid.position.Y());
        }
        else if(boid.position.X() < 1)
        {
            boid.position = Vector2D(_width - 1, boid.position.Y());
        }

        if(boid.position.Y() > _height - 1)
        {
            boid.position = Vector2D(boid.position.X(), 1);
        }
        else if(boid.position.Y() < 1)
        {
            boid.position = Vector2D(boid.position.X(), _height - 1);
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
                "Unable to load texture " + texturePath + "! SDL_image Error: " + IMG_GetError() +
                "\n");
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

        return texture;
    }

    void Window::Render(Boid& boid) const
    {
        SDL_Rect renderQuad = {static_cast<int>(boid.position.X()) - (boid.GetTexture()->width / 2),
                               static_cast<int>(boid.position.Y()) - ((boid.GetTexture()->height * 5) / 6),
                               boid.GetTexture()->width,
                               boid.GetTexture()->height};

        boid.center.x = boid.GetTexture()->width / 2;
        boid.center.y = (boid.GetTexture()->height * 5) / 6;

        auto result = SDL_RenderCopyEx(
            _renderer, boid.GetTexture()->texture, nullptr, &renderQuad, boid.angle, &(boid.center), boid.flip);

        if(result == -1)
        {
            throw Exception("Boid rendering failed. " + std::string{SDL_GetError()});
        }
    }

    int Window::GetWidth() const
    {
        return _width;
    }

    int Window::GetHeight() const
    {
        return _height;
    }

    std::vector<SDL_Point>* Window::GetObstacles()
    {
        return &_obstacles;
    }

}