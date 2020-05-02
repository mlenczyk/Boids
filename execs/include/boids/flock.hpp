#pragma once

#include <vector>

#include "texture.hpp"
#include "window.hpp"

namespace flocking_simulation
{
    class Flock
    {
    public:
        Flock(int boidsCount, std::string texturePath, Window* window);

        void Run();

    private:
        void Initialize();

        const int _boidsCount;
        const Texture _boidsTexture;
        Window* _window;
        std::vector<Boid> _boids;
        std::vector<Boid> _boidsSnapshot;
    };
}