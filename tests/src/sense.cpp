#pragma once

#include "gtest/gtest.h"

#include "boids/boid.hpp"
#include "boids/sense.hpp"
#include "boids/vector2d.hpp"

using namespace flocking_simulation;

namespace
{
    void CheckVectorsEquality(Vector2D expected, Vector2D actual)
    {
        ASSERT_NEAR(expected.X(), actual.X(), 0.001);
        ASSERT_NEAR(expected.Y(), actual.Y(), 0.001);
    }

    TEST(AlignmentPerceive, NoBoidInRange)
    {
        auto alignmentSense = AlignmentSense(100, Vector2D(), Vector2D());

        std::vector<Boid> boids;
        boids.push_back(Boid{Vector2D(160, 0), Vector2D(), nullptr});

        auto result = alignmentSense.Perceive(boids);

        CheckVectorsEquality(Vector2D(), result);
    }

    TEST(AlignmentPerceive, BoidInRange)
    {
        auto alignmentSense = AlignmentSense(100, Vector2D(), Vector2D());
        std::vector<Boid> boids;

        boids.push_back(Boid{Vector2D(6, 0), Vector2D(1.123, 0), nullptr});
        boids.push_back(Boid{Vector2D(3, 0), Vector2D(2.123, 0), nullptr});

        auto result = alignmentSense.Perceive(boids);

        CheckVectorsEquality(Vector2D(3.246 / 2, 0), result);
    }

    TEST(SeparationPerceive, NoBoidInRange)
    {
        auto separationSense = SeparationSense(100, Vector2D());

        std::vector<Boid> boids;
        boids.push_back(Boid{Vector2D(160, 0), Vector2D(), nullptr});

        auto result = separationSense.Perceive(boids);

        CheckVectorsEquality(Vector2D(), result);
    }

    TEST(SeparationPerceive, BoidInRange_XNeedsSeparation)
    {
        std::vector<Boid> boids;
        boids.push_back(Boid{Vector2D(0, 0), Vector2D(1, 0), nullptr});
        boids.push_back(Boid{Vector2D(6, 0), Vector2D(-1, 0), nullptr});

        auto separationSense1 = SeparationSense(100, Vector2D());
        auto result1 = separationSense1.Perceive(boids);
        auto separationSense2 = SeparationSense(100, Vector2D(6, 0));
        auto result2 = separationSense2.Perceive(boids);

        CheckVectorsEquality(Vector2D(-0.166, 0), result1);
        CheckVectorsEquality(Vector2D(0.166, 0), result2);
    }

    TEST(SeparationPerceive, BoidInRange_YNeedsSeparation)
    {
        auto separationSense = SeparationSense(100, Vector2D());
        std::vector<Boid> boids;

        boids.push_back(Boid{Vector2D(0, 6), Vector2D(1.123, 0), nullptr});

        auto result = separationSense.Perceive(boids);

        CheckVectorsEquality(Vector2D(0, -0.166), result);
    }

    TEST(SeparationPerceive, BoidInRange_XYNeedsSeparation)
    {
        auto separationSense = SeparationSense(100, Vector2D());
        std::vector<Boid> boids;

        boids.push_back(Boid{Vector2D(6, 6), Vector2D(1.123, 0), nullptr});

        auto result = separationSense.Perceive(boids);

        CheckVectorsEquality(Vector2D(-0.166, -0.166), result);
    }
}