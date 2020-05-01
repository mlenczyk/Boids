#pragma once

#include <cstdint>
#include <Eigen/Dense>

namespace flocking_simulation
{
    class Vector2D
    {
    public:
        Vector2D() = default;
        Vector2D(float x, float y);

        float X() const;
        float Y() const;

        Vector2D& operator=(const Vector2D& other);

        Vector2D operator+(const Vector2D& other) const;
        Vector2D operator+(float value) const;
        Vector2D& operator+=(const Vector2D& other);

        Vector2D operator-(const Vector2D& other) const;
        Vector2D operator-(float value) const;

        Vector2D operator/(float value) const;

        Vector2D operator*(float value) const;

        bool operator!=(const Vector2D& other) const;
        bool operator==(const Vector2D& other) const;

        float MeasureDistanceBetweenTwoVectors(const Vector2D& other) const;
        float MeasureAngleBetweenTwoVectors(const Vector2D& other) const;
        Vector2D Normalize();
        float Magnitude() const;
        Vector2D SetMagnitude(float x);
        Vector2D Limit(float max);
        float Dot(const Vector2D& other) const;
        float Determinant(const Vector2D& other) const;

    private:
        using UnderlyingType = Eigen::Vector2d;

        UnderlyingType _v = {};

        Vector2D(UnderlyingType v);
    };
}