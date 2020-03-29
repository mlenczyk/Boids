#include <array>
#include <iostream>
#include <vector>

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
    static constexpr double VelocityMin = -1;
    static constexpr double VelocityMax = 1;
    try
    {
        Window window("Flocking simulation", 800, 600);

        std::vector<Boid> boids;
        double rand1;
        double rand2;
        for(auto i = 0; i < 1000; i++)
        {
            boids.push_back(Boid(
                window.GetRenderer(),
                Vector2D(fRand(50, 750), fRand(50, 550)),
                Vector2D(fRand(VelocityMin, VelocityMax), fRand(VelocityMin, VelocityMax)),
                "E:/Programming/Git/repos/Boids/src/graphics/BoidSmall.png"sv));
        }

        Boid test(
            window.GetRenderer(),
            Vector2D(fRand(100, 700), fRand(100, 500)),
            Vector2D(fRand(-VelocityMin, VelocityMin), fRand(-VelocityMin, VelocityMin)),
            "E:/Programming/Git/repos/Boids/src/graphics/Boid.png"sv);

        while(!window.IsClosed())
        {
            window.PollEvents();
            for(auto& b: boids)
            {
                // auto newVelocity = b.Align(boids);
                auto forceOfAlignment = b.Alignment(boids);
                forceOfAlignment = forceOfAlignment * 1;
                b.ApplyForce(forceOfAlignment);

                b.Update();
                b.Render();
                window.KeepBoidInScreen(b);
                //     // b.velocity += Vector2D(0.0001, -0.000001);
            }
            test.Update();
            test.Render();
            window.KeepBoidInScreen(test);

            window.UpdateWindow();
            // SDL_Delay(1);
            // printf("loop.\r\n");
        }
    }
    catch(Exception& e)
    {
        printf(e.what());
    }

    return 0;
}