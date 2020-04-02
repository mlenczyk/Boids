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
    static constexpr double VelocityMin = -5;
    static constexpr double VelocityMax = 5;

    try
    {
        Window window("Flocking simulation", 800, 600);

        const auto boidSmallTexture = window.LoadTexture("graphics/BoidSmall.png");

        std::vector<Boid> boids;
        for(auto i = 0; i < 50; i++)
        {
            boids.push_back(Boid(
                Vector2D(fRand(50, 750), fRand(50, 550)),
                Vector2D(fRand(VelocityMin, VelocityMax), fRand(VelocityMin, VelocityMax)),
                boidSmallTexture));
        }

        std::vector<Boid> boidsSnapshot;

        while(!window.IsClosed())
        {
                        window.PollEvents();

            for(int i = 0; i < boids.size(); i++)
                boidsSnapshot.push_back(boids[i]);

            for(int i = 0; i < boids.size(); i++)
            {
                auto forceOfAlignment = boids[i].Alignment(boids);
                forceOfAlignment = forceOfAlignment * 1;

                // auto forceOfSeparation = boids[i].Separation(boids);
                // forceOfSeparation = forceOfSeparation * 1;

                boidsSnapshot[i].ApplyForce(forceOfAlignment);
                // boidsSnapshot[i].ApplyForce(forceOfSeparation);

                boidsSnapshot[i].Update();
            }

            for(int i = 0; i < boidsSnapshot.size(); i++)
            {
                window.Render(boidsSnapshot[i]);
                window.KeepBoidInScreen(boidsSnapshot[i]);
                // SDL_Delay(1);
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