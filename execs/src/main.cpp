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

    static constexpr int width = 800;
    static constexpr int height = 600;

    try
    {
        Window window("Flocking simulation", width, height);

        auto boidSmallTexture = window.LoadTexture("graphics/BoidSmall.png");
        auto boidTexture = window.LoadTexture("graphics/BoidSmall.png");

        std::vector<Boid> boids;
        for(auto i = 0; i < 200; i++)
        {
            boids.push_back(Boid(
                Vector2D(fRand(50, 750), fRand(50, 550)),
                Vector2D(fRand(VelocityMin, VelocityMax), fRand(VelocityMin, VelocityMax)),
                &boidSmallTexture));
        }

        std::vector<Boid> boidsSnapshot = boids;

        while(!window.IsClosed())
        {
            window.PollEvents();

            for(int i = 0; i < boids.size(); i++)
            {
                auto forceOfAlignment = boids[i].Alignment(boids);
                forceOfAlignment = forceOfAlignment * 0.2;

                auto forceOfSeparation = boids[i].Separation(boids);
                forceOfSeparation = forceOfSeparation * 0.8;

                auto forceOfCohesion = boids[i].Cohesion(boids);
                forceOfCohesion = forceOfCohesion * 0.4;

                boidsSnapshot[i].ApplyForce(forceOfAlignment);
                boidsSnapshot[i].ApplyForce(forceOfSeparation);
                boidsSnapshot[i].ApplyForce(forceOfCohesion);

                boidsSnapshot[i].Update();

                window.KeepBoidInScreen(boidsSnapshot[i]);
                window.Render(boidsSnapshot[i]);
            }

            window.UpdateWindow();
            boids = boidsSnapshot;
        }
    }
    catch(Exception& e)
    {
        printf(e.what());
    }

    return 0;
}