#pragma once

#include <cstdint>

class Vector2D
{
public:
    Vector2D() = default;
    Vector2D(double x, double y);

    void Update(double x, double y);
    double X() const;
    double Y() const;

    Vector2D& operator=(const Vector2D& other);

    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator+(double value) const;

    Vector2D operator-(const Vector2D& other) const;
    Vector2D operator-(double value) const;

    Vector2D& operator+=(const Vector2D& other);

    Vector2D operator/(const Vector2D& other) const;
    Vector2D operator/(double value) const;

    Vector2D operator*(const Vector2D& other) const;
    Vector2D operator*(double value) const;

    bool operator<(const Vector2D& other) const;
    bool operator>(const Vector2D& other) const;
    bool operator!=(const Vector2D& other) const;

    // Vector2D AddTwoVectors(const Vector2D& a, const Vector2D& b);
    static double MeasureDistanceBetweenTwoVectors(const Vector2D& reference, const Vector2D& other);
    static double MeasureAngleBetweenTwoVectors(const Vector2D& reference, const Vector2D& other);
    void Normalize();
    double Magnitude() const;
    void SetMagnitude(double x);
    void Limit(double max);

private:
    double _x;
    double _y;
};
