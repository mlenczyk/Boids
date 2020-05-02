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

        for(auto& boid: boids)
        {
            auto distance = boids[0].position.MeasureDistanceBetweenTwoVectors(boid.position);
            boids[0].Separation(distance, boid.position);
        }

        for(auto& boid: boids)
        {
            auto distance = boids[1].position.MeasureDistanceBetweenTwoVectors(boid.position);
            boids[1].Separation(distance, boid.position);
        }

        auto result1 = boids[0].GetSeparationImpulse();
        auto result2 = boids[1].GetSeparationImpulse();

        CheckVectorsEquality(Vector2D(-0.1, 0), result1);
        CheckVectorsEquality(Vector2D(0.1, 0), result2);
    }

    TEST(SeparationSense, CloseAndSimple)
    {
        std::vector<Boid> boids;

        boids.push_back(Boid{Vector2D(), Vector2D(), nullptr});
        boids.push_back(Boid{Vector2D(0.1, 0), Vector2D(), nullptr});

        for(auto& boid: boids)
        {
            auto distance = boids[0].position.MeasureDistanceBetweenTwoVectors(boid.position);
            boids[0].Separation(distance, boid.position);
        }

        for(auto& boid: boids)
        {
            auto distance = boids[1].position.MeasureDistanceBetweenTwoVectors(boid.position);
            boids[1].Separation(distance, boid.position);
        }

        auto result1 = boids[0].GetSeparationImpulse();
        auto result2 = boids[1].GetSeparationImpulse();

        CheckVectorsEquality(Vector2D(-1, 0), result1);
        CheckVectorsEquality(Vector2D(1, 0), result2);
    }

    TEST(SeparationSense, FarAndComplex)
    {
        std::vector<Boid> boids;

        boids.push_back(Boid{Vector2D(), Vector2D(), nullptr});
        boids.push_back(Boid{Vector2D(10, 10), Vector2D(), nullptr});

        for(auto& boid: boids)
        {
            auto distance = boids[0].position.MeasureDistanceBetweenTwoVectors(boid.position);
            boids[0].Separation(distance, boid.position);
        }

        for(auto& boid: boids)
        {
            auto distance = boids[1].position.MeasureDistanceBetweenTwoVectors(boid.position);
            boids[1].Separation(distance, boid.position);
        }

        auto result1 = boids[0].GetSeparationImpulse();
        auto result2 = boids[1].GetSeparationImpulse();

        CheckVectorsEquality(Vector2D(-0.1, -0.1), result1);
        CheckVectorsEquality(Vector2D(0.1, 0.1), result2);
    }

    TEST(SeparationSense, CloseAndComplex)
    {
        std::vector<Boid> boids;

        boids.push_back(Boid{Vector2D(), Vector2D(), nullptr});
        boids.push_back(Boid{Vector2D(0.1, 0.1), Vector2D(), nullptr});

        for(auto& boid: boids)
        {
            auto distance = boids[0].position.MeasureDistanceBetweenTwoVectors(boid.position);
            boids[0].Separation(distance, boid.position);
        }

        for(auto& boid: boids)
        {
            auto distance = boids[1].position.MeasureDistanceBetweenTwoVectors(boid.position);
            boids[1].Separation(distance, boid.position);
        }

        auto result1 = boids[0].GetSeparationImpulse();
        auto result2 = boids[1].GetSeparationImpulse();

        CheckVectorsEquality(Vector2D(-0.707, -0.707), result1);
        CheckVectorsEquality(Vector2D(0.707, 0.707), result2);
    }

    // Cohesion

    TEST(CohesionSense, Simple)
    {
        std::vector<Boid> boids;

        boids.push_back(Boid{Vector2D(), Vector2D(), nullptr});
        boids.push_back(Boid{Vector2D(10, 0), Vector2D(), nullptr});

        for(auto& boid: boids)
        {
            auto distance = boids[0].position.MeasureDistanceBetweenTwoVectors(boid.position);
            boids[0].Cohesion(distance, boid.position);
        }

        for(auto& boid: boids)
        {
            auto distance = boids[1].position.MeasureDistanceBetweenTwoVectors(boid.position);
            boids[1].Cohesion(distance, boid.position);
        }

        auto result1 = boids[0].GetCohesionImpulse();
        auto result2 = boids[1].GetCohesionImpulse();

        CheckVectorsEquality(Vector2D(1, 0), result1);
        CheckVectorsEquality(Vector2D(-1, 0), result2);
    }

    TEST(CohesionSense, Complex)
    {
        std::vector<Boid> boids;

        boids.push_back(Boid{Vector2D(), Vector2D(), nullptr});
        boids.push_back(Boid{Vector2D(40, 40), Vector2D(), nullptr});

        for(auto& boid: boids)
        {
            auto distance = boids[0].position.MeasureDistanceBetweenTwoVectors(boid.position);
            boids[0].Cohesion(distance, boid.position);
        }

        for(auto& boid: boids)
        {
            auto distance = boids[1].position.MeasureDistanceBetweenTwoVectors(boid.position);
            boids[1].Cohesion(distance, boid.position);
        }

        auto result1 = boids[0].GetCohesionImpulse();
        auto result2 = boids[1].GetCohesionImpulse();

        CheckVectorsEquality(Vector2D(0.707, 0.707), result1);
        CheckVectorsEquality(Vector2D(-0.707, -0.707), result2);
    }

    // Alignment

    TEST(AlignmentSense, Simple)
    {
        std::vector<Boid> boids;

        boids.push_back(Boid{Vector2D(6, 0), Vector2D(1.123, 0), nullptr});
        boids.push_back(Boid{Vector2D(3, 0), Vector2D(2.123, 0), nullptr});

        for(auto& boid: boids)
        {
            auto distance = boids[0].position.MeasureDistanceBetweenTwoVectors(boid.position);
            boids[0].Alignment(distance, boid.velocity);
        }

        for(auto& boid: boids)
        {
            auto distance = boids[1].position.MeasureDistanceBetweenTwoVectors(boid.position);
            boids[1].Alignment(distance, boid.velocity);
        }

        auto result1 = boids[0].GetAlignmentImpulse();
        auto result2 = boids[1].GetAlignmentImpulse();

        CheckVectorsEquality(Vector2D((3.246 / 2) - 1.123, 0), result1);
        CheckVectorsEquality(Vector2D((3.246 / 2) - 2.123, 0), result2);
    }

}