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
    static constexpr double VelocityRange = 0.0001;
    try
    {
        Window window("Boids - flocking simulation", 800, 600);
        Boid boidUp(
            window.GetRenderer(),
            Vector2D(400, 300),
            Vector2D(0, -0.05),
            "E:/Programming/Git/repos/Boids/src/graphics/Boid.png"sv);
        Boid boidRight(
            window.GetRenderer(),
            Vector2D(400, 300),
            Vector2D(0.05, 0),
            "E:/Programming/Git/repos/Boids/src/graphics/Boid.png"sv);
        Boid boidDown(
            window.GetRenderer(),
            Vector2D(400, 300),
            Vector2D(0, 0.05),
            "E:/Programming/Git/repos/Boids/src/graphics/Boid.png"sv);
        Boid boidLeft(
            window.GetRenderer(),
            Vector2D(400, 300),
            Vector2D(-0.05, 0),
            "E:/Programming/Git/repos/Boids/src/graphics/Boid.png"sv);
        Boid boidLeftUp(
            window.GetRenderer(),
            Vector2D(400, 300),
            Vector2D(-0.05, -0.05),
            "E:/Programming/Git/repos/Boids/src/graphics/Boid.png"sv);

        while(!window.IsClosed())
        {
            boidUp.Update();
            boidUp.Render();
            boidUp.velocity += Vector2D(0.0001, -0.000001);

            boidRight.Update();
            boidRight.Render();
            boidRight.velocity += Vector2D(0.0001, -0.000001);

            boidDown.Update();
            boidDown.Render();
            boidDown.velocity += Vector2D(0.0001, -0.000001);

            boidLeft.Update();
            boidLeft.Render();
            boidLeft.velocity += Vector2D(0.0001, -0.000001);

            boidLeftUp.Update();
            boidLeftUp.Render();
            boidLeftUp.velocity += Vector2D(0.0001, -0.000001);

            window.UpdateWindow();
            window.PollEvents();
            window.Clear();
            SDL_Delay(1);
        }
    }
    catch(Exception& e)
    {
        printf(e.what());
    }

    return 0;
}