#include <iostream>

#include "boids/exception.hpp"
#include "boids/flock.hpp"
#include "boids/window.hpp"

using namespace flocking_simulation;

int main(int argc, char* argv[])
{
    static constexpr int width = 800;
    static constexpr int height = 600;

    static constexpr int boidsCount = 100;
    static const std::string boidsTexturePath = "graphics/BoidSmall.png";

    try
    {
        Window window("Flocking simulation", width, height);

        Flock flock(boidsCount, boidsTexturePath, &window);
        flock.Run();
    }
    catch(Exception& e)
    {
        printf(e.what());
    }

    return 0;
}