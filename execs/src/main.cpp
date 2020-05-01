#include <iostream>
#include <random>
#include <type_traits>
#include <vector>
#include <time.h>

#include "SDL.h"
#include "boids/boid.hpp"
#include "boids/exception.hpp"
#include "boids/window.hpp"

using namespace std;
using namespace flocking_simulation;

class RandomGenerator
{
public:
    template <typename T> static constexpr T Draw(T min, T max) throw(Exception)
    {
        if(!std::is_arithmetic<T>::value)
        {
            throw Exception("Wrong type in random generator.");
        }
        auto distribution = std::uniform_real_distribution<float>(min, max);

        return static_cast<T>(distribution(std::mt19937{std::random_device{}()}));
    };

private:
    RandomGenerator() = delete;
};

int main(int argc, char* argv[])
{
    static constexpr float VelocityMin = -1.5;
    static constexpr float VelocityMax = 1.5;

    static constexpr int width = 800;
    static constexpr int height = 600;

    try
    {
        Window window("Flocking simulation", width, height);

        auto boidSmallTexture = window.LoadTexture("graphics/BoidSmall.png");

        std::vector<Boid> boids;
        for(auto i = 0; i < 100; i++)
        {
            boids.push_back(Boid(
                Vector2D(RandomGenerator::Draw(21, width - 21), RandomGenerator::Draw(21, height - 21)),
                Vector2D(
                    RandomGenerator::Draw(VelocityMin, VelocityMax),
                    RandomGenerator::Draw(VelocityMin, VelocityMax)),
                &boidSmallTexture));
        }

        std::vector<Boid> boidsSnapshot = boids;

        while(!window.IsClosed())
        {
            auto loopBeginning = SDL_GetTicks();
            window.PollEvents();

            auto beforeBoidIter = SDL_GetTicks();
            for(int i = 0; i < boids.size(); i++)
            {
                auto beforeAlignment = SDL_GetTicks();
                auto forceOfAlignment = boids[i].Alignment(boids);
                forceOfAlignment = forceOfAlignment * 0.2;

                auto beforeCohesion = SDL_GetTicks();
                auto forceOfCohesion = boids[i].Cohesion(boids);
                forceOfCohesion = forceOfCohesion * 0.3;

                auto beforeSeparation = SDL_GetTicks();
                auto forceOfSeparation = boids[i].Separation(boids);
                forceOfSeparation = forceOfSeparation * 1.2;

                auto beforeApplyingForce = SDL_GetTicks();
                boidsSnapshot[i].ApplyForce(forceOfAlignment);
                boidsSnapshot[i].ApplyForce(forceOfCohesion);
                boidsSnapshot[i].ApplyForce(forceOfSeparation);

                auto beforeUpdate = SDL_GetTicks();
                boidsSnapshot[i].Update();

                window.KeepBoidInScreen(boidsSnapshot[i]);
                window.Render(boidsSnapshot[i]);

                // printf("alignmend: %d\r\n", beforeCohesion - beforeAlignment);
                // printf("cohesion: %d\r\n", beforeSeparation - beforeCohesion);
                // printf("separation: %d\r\n", beforeApplyingForce - beforeSeparation);
                // printf("applyForce: %d\r\n", beforeUpdate - beforeApplyingForce);
                // printf("updateAndRender: %d\r\n", SDL_GetTicks() - beforeUpdate);
            }

            auto beforeUpdateWindow = SDL_GetTicks();
            window.UpdateWindow();

            boids = boidsSnapshot;

            auto endOfLoop = SDL_GetTicks();
            printf("__________________\r\n");
            printf("pollEvents: %d\r\n", beforeBoidIter - loopBeginning);
            printf("boidIter: %d\r\n", beforeUpdateWindow - beforeBoidIter);
            printf("windowUpdate: %d\r\n", endOfLoop - beforeUpdateWindow);
        }
    }
    catch(Exception& e)
    {
        printf(e.what());
    }

    return 0;
}