#pragma once

#include "gtest/gtest.h"

#include "boids/boid.hpp"
#include "boids/vector2d.hpp"

using namespace flocking_simulation;

namespace
{
    void CheckVectorsEquality(Vector2D expected, Vector2D actual)
    {
        ASSERT_EQ(expected.X(), actual.X());
        ASSERT_EQ(expected.Y(), actual.Y());
    }

    TEST(Test, Test)
    {
        ASSERT_TRUE(true);
    }

    TEST(BoidPerceiveSurroundingBoidsAndReturnTheirAverageVelocity, NoBoidInRange)
    {
        std::vector<Boid> boids;

        boids.push_back(Boid{Vector2D(), Vector2D(), nullptr});
        boids.push_back(Boid{Vector2D(160, 0), Vector2D(), nullptr});

        auto result = boids[0].PerceiveSurroundingBoidsAndReturnTheirAverageVelocity(boids);

        CheckVectorsEquality(Vector2D(), result);
    }

    TEST(BoidPerceiveSurroundingBoidsAndReturnTheirAverageVelocity, BoidInRange)
    {
        std::vector<Boid> boids;

        boids.push_back(Boid{Vector2D(), Vector2D(), nullptr});
        boids.push_back(Boid{Vector2D(6, 0), Vector2D(1, 0), nullptr});

        auto result = boids[0].PerceiveSurroundingBoidsAndReturnTheirAverageVelocity(boids);

        CheckVectorsEquality(Vector2D(1, 0), result);
    }

    TEST(CalculateAlignmentVelocity, BoidInRange)
    {
        auto boid = Boid(Vector2D(), Vector2D(0, 0), nullptr);

        auto result = boid.CalculateAlignmentVelocity(Vector2D(1, 0));

        CheckVectorsEquality(Vector2D(1, 0), result);
    }

}