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
        Boid boidSkos(
            window.GetRenderer(),
            Vector2D(400, 300),
            Vector2D(-0.05, -0.05),
            "E:/Programming/Git/repos/Boids/src/graphics/Boid.png"sv);
        // std::array<Boid, 10> boids{
        //     Boid(
        //         window.GetRenderer(),
        //         Vector2D(400, 300),
        //         Vector2D(fRand(-VelocityRange, VelocityRange), fRand(-VelocityRange,
        //         VelocityRange)), "E:/Programming/Git/repos/Boids/src/graphics/Boid.png"sv),
        //     Boid(
        //         window.GetRenderer(),
        //         Vector2D(400, 300),
        //         Vector2D(fRand(-VelocityRange, VelocityRange), fRand(-VelocityRange,
        //         VelocityRange)), "E:/Programming/Git/repos/Boids/src/graphics/Boid.png"sv),
        //     Boid(
        //         window.GetRenderer(),
        //         Vector2D(400, 300),
        //         Vector2D(fRand(-VelocityRange, VelocityRange), fRand(-VelocityRange,
        //         VelocityRange)), "E:/Programming/Git/repos/Boids/src/graphics/Boid.png"sv),
        //     Boid(
        //         window.GetRenderer(),
        //         Vector2D(400, 300),
        //         Vector2D(fRand(-VelocityRange, VelocityRange), fRand(-VelocityRange,
        //         VelocityRange)), "E:/Programming/Git/repos/Boids/src/graphics/Boid.png"sv),
        //     Boid(
        //         window.GetRenderer(),
        //         Vector2D(400, 300),
        //         Vector2D(fRand(-VelocityRange, VelocityRange), fRand(-VelocityRange,
        //         VelocityRange)), "E:/Programming/Git/repos/Boids/src/graphics/Boid.png"sv),
        //     Boid(
        //         window.GetRenderer(),
        //         Vector2D(400, 300),
        //         Vector2D(fRand(-VelocityRange, VelocityRange), fRand(-VelocityRange,
        //         VelocityRange)), "E:/Programming/Git/repos/Boids/src/graphics/Boid.png"sv),
        //     Boid(
        //         window.GetRenderer(),
        //         Vector2D(400, 300),
        //         Vector2D(fRand(-VelocityRange, VelocityRange), fRand(-VelocityRange,
        //         VelocityRange)), "E:/Programming/Git/repos/Boids/src/graphics/Boid.png"sv),
        //     Boid(
        //         window.GetRenderer(),
        //         Vector2D(400, 300),
        //         Vector2D(fRand(-VelocityRange, VelocityRange), fRand(-VelocityRange,
        //         VelocityRange)), "E:/Programming/Git/repos/Boids/src/graphics/Boid.png"sv),
        //     Boid(
        //         window.GetRenderer(),
        //         Vector2D(400, 300),
        //         Vector2D(fRand(-VelocityRange, VelocityRange), fRand(-VelocityRange,
        //         VelocityRange)), "E:/Programming/Git/repos/Boids/src/graphics/Boid.png"sv),
        //     Boid(
        //         window.GetRenderer(),
        //         Vector2D(400, 300),
        //         Vector2D(fRand(-VelocityRange, VelocityRange), fRand(-VelocityRange,
        //         VelocityRange)), "E:/Programming/Git/repos/Boids/src/graphics/Boid.png"sv)};

        while(!window.IsClosed())
        {
            boidUp.Update();
            boidUp.Render();

            boidRight.Update();
            boidRight.Render();

            boidDown.Update();
            boidDown.Render();

            boidLeft.Update();
            boidLeft.Render();

            boidSkos.Update();
            boidSkos.Render();

            window.UpdateWindow();
            window.PollEvents();
            window.Clear();
            // SDL_Delay(1);
        }
    }
    catch(Exception& e)
    {
        printf(e.what());
    }

    return 0;
}