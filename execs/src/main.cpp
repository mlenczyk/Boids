#include <array>
#include <iostream>

#include "boid.hpp"
#include "exception.hpp"
#include "window.hpp"

using namespace std;

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int main(int argc, char* argv[])
{
    static constexpr double VelocityRange = 0.05;
    try
    {
        Window window("Boids - flocking simulation", 800, 600);
        // Boid boid(
        //     window.GetRenderer(),
        //     Vector2D(400, 300),
        //     Vector2D(fRand(-VelocityRange, VelocityRange), fRand(-VelocityRange, VelocityRange)),
        //     "E:/Programming/Git/repos/Boids/src/graphics/Boid.png"sv);

        Boid boid(
            window.GetRenderer(),
            Vector2D(400, 300),
            Vector2D(0, -0.05),
            "E:/Programming/Git/repos/Boids/src/graphics/Boid.png"sv);

        while(!window.IsClosed())
        {
            window.PollEvents();
            boid.Update();
            window.Clear();
            boid.Render();
            SDL_RenderPresent(window.GetRenderer());
            // SDL_Delay(1);
        }
    }
    catch(Exception& e)
    {
        printf(e.what());
    }

    return 0;
}