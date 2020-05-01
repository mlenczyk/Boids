#include "gtest/gtest.h"

#include "boids/boid.hpp"
#include "boids/vector2d.hpp"

using namespace flocking_simulation;

namespace
{
    void CheckVectorsEquality(Vector2D expected, Vector2D actual)
    {
        ASSERT_NEAR(expected.X(), actual.X(), 0.001);
        ASSERT_NEAR(expected.Y(), actual.Y(), 0.001);
    }

    // Separation

    TEST(SeparationSense, FarAndSimple)
    {
        std::vector<Boid> boids;

        boids.push_back(Boid{Vector2D(), Vector2D(), nullptr});
        boids.push_back(Boid{Vector2D(10, 0), Vector2D(), nullptr});

        auto result1 = boids[0].Separation(boids);
        auto result2 = boids[1].Separation(boids);

        CheckVectorsEquality(Vector2D(-0.1, 0), result1);
        CheckVectorsEquality(Vector2D(0.1, 0), result2);
    }

    TEST(SeparationSense, CloseAndSimple)
    {
        std::vector<Boid> boids;

        boids.push_back(Boid{Vector2D(), Vector2D(), nullptr});
        boids.push_back(Boid{Vector2D(0.1, 0), Vector2D(), nullptr});

        auto result1 = boids[0].Separation(boids);
        auto result2 = boids[1].Separation(boids);

        CheckVectorsEquality(Vector2D(-1, 0), result1);
        CheckVectorsEquality(Vector2D(1, 0), result2);
    }

    TEST(SeparationSense, FarAndComplex)
    {
        std::vector<Boid> boids;

        boids.push_back(Boid{Vector2D(), Vector2D(), nullptr});
        boids.push_back(Boid{Vector2D(10, 10), Vector2D(), nullptr});

        auto result1 = boids[0].Separation(boids);
        auto result2 = boids[1].Separation(boids);

        CheckVectorsEquality(Vector2D(-0.1, -0.1), result1);
        CheckVectorsEquality(Vector2D(0.1, 0.1), result2);
    }

    TEST(SeparationSense, CloseAndComplex)
    {
        std::vector<Boid> boids;

        boids.push_back(Boid{Vector2D(), Vector2D(), nullptr});
        boids.push_back(Boid{Vector2D(0.1, 0.1), Vector2D(), nullptr});

        auto result1 = boids[0].Separation(boids);
        auto result2 = boids[1].Separation(boids);

        CheckVectorsEquality(Vector2D(-0.707, -0.707), result1);
        CheckVectorsEquality(Vector2D(0.707, 0.707), result2);
    }

    // Cohesion

    TEST(CohesionSense, Simple)
    {
        std::vector<Boid> boids;

        boids.push_back(Boid{Vector2D(), Vector2D(), nullptr});
        boids.push_back(Boid{Vector2D(10, 0), Vector2D(), nullptr});

        auto result1 = boids[0].Cohesion(boids);
        auto result2 = boids[1].Cohesion(boids);

        CheckVectorsEquality(Vector2D(1, 0), result1);
        CheckVectorsEquality(Vector2D(-1, 0), result2);
    }

    TEST(CohesionSense, Complex)
    {
        std::vector<Boid> boids;

        boids.push_back(Boid{Vector2D(), Vector2D(), nullptr});
        boids.push_back(Boid{Vector2D(100, 100), Vector2D(), nullptr});

        auto result1 = boids[0].Cohesion(boids);
        auto result2 = boids[1].Cohesion(boids);

        CheckVectorsEquality(Vector2D(0.707, 0.707), result1);
        CheckVectorsEquality(Vector2D(-0.707, -0.707), result2);
    }

}