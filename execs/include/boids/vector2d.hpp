#pragma once

#include <cstdint>
#include <Eigen/Dense>

// namespace eigenVectorHelpers
// {
//     using Vector2D = Eigen::Vector2d;
//     double MeasureDistanceBetweenTwoVectors(const Vector2D& reference, const Vector2D& other);
//     double MeasureAngleBetweenTwoVectors(const Vector2D& reference, const Vector2D& other);

// }

class Vector2D
{
public:
    Vector2D() = default;
    Vector2D(double x, double y);

    Vector2D GetVector() const;

    double X() const;
    double Y() const;

    Vector2D& operator=(const Vector2D& other);

    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator+(double value) const;
    Vector2D& operator+=(const Vector2D& other);

    Vector2D operator-(const Vector2D& other) const;
    Vector2D operator-(double value) const;

    Vector2D operator/(double value) const;

    Vector2D operator*(double value) const;

    bool operator<(const Vector2D& other) const;
    bool operator>(const Vector2D& other) const;
    bool operator!=(const Vector2D& other) const;
    bool operator==(const Vector2D& other) const;

    double MeasureDistanceBetweenTwoVectors(const Vector2D& other) const;
    double MeasureAngleBetweenTwoVectors(const Vector2D& other) const;
    void Normalize();
    double Magnitude() const;
    void SetMagnitude(double x);
    void Limit(double max);
    double Dot(const Vector2D& other) const;
    double Determinant(const Vector2D& other) const;

private:
    using UnderlyingType = Eigen::Vector2d;

    UnderlyingType _v = {};

    Vector2D(UnderlyingType v);
};
