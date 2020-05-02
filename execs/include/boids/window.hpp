#pragma once

#include <SDL.h>
#include "boid.hpp"
#include "texture.hpp"

namespace flocking_simulation
{
    class Window
    {
    public:
        Window(const std::string title, int width, int height);
        ~Window();

        void PollEvents();
        bool IsClosed() const;
        void UpdateWindow();
        void KeepBoidInScreen(Boid& boid) const;
        Texture LoadTexture(std::string texturePath) const;
        void Render(Boid& boid) const;

        int GetWidth() const;
        int GetHeight() const;

        void AddObstaclePoint(int x, int y);
        void DeleteObstaclePoint(int x, int y);
        std::vector<SDL_Point>* GetObstacles();

    private:
        bool Init();
        void Clear() const;
        void DrawPoints(const std::vector<SDL_Point>& points);

        const std::string _title;
        const int _width;
        const int _height;

        bool _shouldBeClosed = false;
        SDL_Window* _window = nullptr;
        SDL_Renderer* _renderer = nullptr;

        std::vector<SDL_Point> _obstacles;
    };
}