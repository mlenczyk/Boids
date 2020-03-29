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
        for(auto i = 0; i < 1000; i++)
        {
            boids.push_back(Boid(
                window.GetRenderer(),
                Vector2D(fRand(50, 750), fRand(50, 550)),
                Vector2D(fRand(VelocityMin, VelocityMax), fRand(VelocityMin, VelocityMax)),
                "./graphics/BoidSmall.png"));
        }
        Boid test(
            window.GetRenderer(),
            Vector2D(fRand(100, 700), fRand(100, 500)),
            Vector2D(fRand(-VelocityMin, VelocityMin), fRand(-VelocityMin, VelocityMin)),
            "E:/Programming/Git/repos/Boids/src/graphics/Boid.png");
        // SDL_Delay(2000);

        while(!window.IsClosed())
        {
            window.PollEvents();
            for(auto& b: boids)
            {
                auto forceOfAlignment = b.Alignment(boids);
                forceOfAlignment = forceOfAlignment * 1;
                b.ApplyForce(forceOfAlignment);

                b.Update();
                b.Render();
                window.KeepBoidInScreen(b);
            }

            window.UpdateWindow();
        }
    }
    catch(Exception& e)
    {
        printf(e.what());
    }

    return 0;
}