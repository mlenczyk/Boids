#pragma once

#include "gtest/gtest.h"

#include "boids/vector2d.hpp"

using namespace testing;

namespace
{
    void CheckVectorsEquality(Vector2D expected, Vector2D actual)
    {
        ASSERT_NEAR(expected.X(), actual.X(), 0.001);
        ASSERT_NEAR(expected.Y(), actual.Y(), 0.001);
    }

    class Vector2DTest : public testing::Test
    {
    };

    TEST_F(Vector2DTest, X)
    {
        auto vector = Vector2D(1, 2);

        auto x = vector.X();

        ASSERT_EQ(1, x);
    }

    TEST_F(Vector2DTest, Y)
    {
        auto vector = Vector2D(1, 2);

        auto y = vector.Y();

        ASSERT_EQ(2, y);
    }

    TEST_F(Vector2DTest, MeasureDistanceBetweenTwoVectors)
    {
        auto vector = Vector2D(1, 1);

        auto dist = vector.MeasureDistanceBetweenTwoVectors(Vector2D(4, 5));

        ASSERT_NEAR(5, dist, 0.001);
    }

    TEST_F(Vector2DTest, MeasureAngleBetweenTwoVectors)
    {
        auto vector = Vector2D(1, 0);

        auto angle = vector.MeasureAngleBetweenTwoVectors(Vector2D(0, 1));

        ASSERT_NEAR(90, angle, 0.001);
    }

    TEST_F(Vector2DTest, Magnitude)
    {
        auto vector = Vector2D(3, 4);

        auto magnitude = vector.Magnitude();

        ASSERT_NEAR(5, magnitude, 0.001);
    }

    TEST_F(Vector2DTest, SetMagnitude)
    {
        auto vector = Vector2D(1, 0);

        vector.SetMagnitude(4);

        ASSERT_EQ(Vector2D(4, 0), vector);
    }

    TEST_F(Vector2DTest, Normalize_YEqualsZero)
    {
        auto vector = Vector2D(3, 0);

        vector.Normalize();

        CheckVectorsEquality(Vector2D(1, 0), vector);
    }

    TEST_F(Vector2DTest, Normalize_XEqualsZero)
    {
        auto vector = Vector2D(0, 5);

        vector.Normalize();

        CheckVectorsEquality(Vector2D(0, 1), vector);
    }

    TEST_F(Vector2DTest, Normalize_XEqualsY)
    {
        auto vector = Vector2D(1, 1);

        vector.Normalize();

        CheckVectorsEquality(Vector2D(0.707107, 0.707107), vector);
    }

    TEST_F(Vector2DTest, Dot)
    {
        auto vector = Vector2D(1, 1);

        auto dot = vector.Dot(Vector2D(2, 2));

        ASSERT_NEAR(4, dot, 0.001);
    }

    TEST_F(Vector2DTest, Determinant)
    {
        auto vector = Vector2D(1, 1);

        auto det = vector.Determinant(Vector2D(2, 2));

        ASSERT_NEAR(0, det, 0.001);
    }
}