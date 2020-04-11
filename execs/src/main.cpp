#include <iostream>
#include <random>
#include <type_traits>
#include <vector>
#include <time.h>

#include "boid.hpp"
#include "exception.hpp"
#include "window.hpp"

using namespace std;

class RandomGenerator
{
public:
    template <typename T> static constexpr T Draw(T min, T max) throw(Exception)
    {
        if(!std::is_arithmetic<T>::value)
        {
            throw Exception("Wrong type in random generator.");
        }
        auto distribution = std::uniform_real_distribution<double>(min, max);

        return static_cast<T>(distribution(std::mt19937{std::random_device{}()}));
    };

private:
    RandomGenerator() = delete;
};

int main(int argc, char* argv[])
{
    static constexpr double VelocityMin = -1.5;
    static constexpr double VelocityMax = 1.5;

    static constexpr int width = 800;
    static constexpr int height = 600;

    try
    {
        Window window("Flocking simulation", width, height);

        auto boidSmallTexture = window.LoadTexture("graphics/BoidSmall.png");
        auto boidTexture = window.LoadTexture("graphics/BoidSmall.png");

        std::vector<Boid> boids;
        for(auto i = 0; i < 100; i++)
        {
            boids.push_back(Boid(
                Vector2D(RandomGenerator::Draw(50, 750), RandomGenerator::Draw(50, 550)),
                Vector2D(
                    RandomGenerator::Draw(VelocityMin, VelocityMax),
                    RandomGenerator::Draw(VelocityMin, VelocityMax)),
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

                /*auto forceOfSeparation = boids[i].Separation(boids);
                forceOfSeparation = forceOfSeparation * 0.8;*/

                auto forceOfCohesion = boids[i].Cohesion(boids);
                forceOfCohesion = forceOfCohesion * 0.4;

                boidsSnapshot[i].ApplyForce(forceOfAlignment);
                // boidsSnapshot[i].ApplyForce(forceOfSeparation);
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