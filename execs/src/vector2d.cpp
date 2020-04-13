#include <cmath>

#include "boids/vector2d.hpp"

// namespace eigenVectorHelpers
// {
//     double MeasureDistanceBetweenTwoVectors(const Vector2D& reference, const Vector2D& other)
//     {
//         return sqrt(pow(other.x() - reference.x(), 2) + pow(other.y() - reference.y(), 2));
//     }

//     double MeasureAngleBetweenTwoVectors(const Vector2D& reference, const Vector2D& other)
//     {
//         auto dot = reference.dot(other);
//         Eigen::Matrix2d matrix;
//         matrix << reference, other;
//         auto det = matrix.determinant();
//         return std::atan2(det, dot) * 180 / 3.14;
//     }

//     // double Vector2D::MeasureDistanceBetweenTwoVectors(const Vector2D& reference, const Vector2D& other)
//     // {
//     //     return sqrt(pow(other.X() - reference.X(), 2) + pow(other.Y() - reference.Y(), 2));
//     // }

//     // double Vector2D::MeasureAngleBetweenTwoVectors(const Vector2D& reference, const Vector2D& other)
//     // {
//     //     auto dot = reference.X() * other.X() + reference.Y() * other.Y();
//     //     auto det = reference.X() * other.Y() - reference.Y() * other.X();
//     //     return std::atan2(det, dot) * 180 / 3.14;
//     // }
// }

Vector2D::Vector2D(double x, double y) : _v(x, y)
{
}

Vector2D::Vector2D(UnderlyingType v) : _v(v)
{
}

double Vector2D::X() const
{
    return _v.x();
}

double Vector2D::Y() const
{
    return _v.y();
}

Vector2D& Vector2D::operator=(const Vector2D& other)
{
    _v = other._v;
    return *this;
}

Vector2D Vector2D::operator+(const Vector2D& other) const
{
    auto v = _v + other._v;
    return Vector2D(v);
}

Vector2D Vector2D::operator+(double value) const
{
    return _v + Vector2D(value, value)._v;
}

Vector2D Vector2D::operator-(const Vector2D& other) const
{
    auto v = _v - other._v;
    return Vector2D(v);
}
Vector2D Vector2D::operator-(double value) const
{
    return _v - Vector2D(value, value)._v;
}

Vector2D& Vector2D::operator+=(const Vector2D& other)
{
    _v = _v + other._v;
    return *this;
}

// Vector2D Vector2D::operator/(const Vector2D& other) const
// {
//     // if(other.X() == 0 || other.Y() == 0)
//     // {
//     //     throw Exception("Zero division in vector");
//     // }
//     // auto x = _x / other.X();
//     // auto y = _y / other.Y();
//     // return Vector2D(x, y);
// }

Vector2D Vector2D::operator/(double value) const
{
    // if(value == 0)
    // {
    //     throw Exception("Zero division in vector");
    // }
    // auto x = _x / value;
    // auto y = _y / value;
    // return Vector2D(x, y);
    auto v = _v / value;
    return Vector2D(v);
}

// Vector2D Vector2D::operator*(const Vector2D& other) const
// {
//     auto x = _x * other.X();
//     auto y = _y * other.Y();
//     return Vector2D(x, y);
// }

Vector2D Vector2D::operator*(double value) const
{
    auto v = _v * value;
    return Vector2D(v);
}

bool Vector2D::operator<(const Vector2D& other) const
{
    return _v.x() < other.X() && _v.y() < other.Y();
}

bool Vector2D::operator>(const Vector2D& other) const
{
    return _v.x() > other.X() && _v.y() > other.Y();
}

bool Vector2D::operator!=(const Vector2D& other) const
{
    return _v != other._v;
}

bool Vector2D::operator==(const Vector2D& other) const
{
    return _v == other._v;
}

double Vector2D::MeasureDistanceBetweenTwoVectors(const Vector2D& other) const
{
    return sqrt(pow(other.X() - _v.x(), 2) + pow(other.Y() - _v.y(), 2));
}

double Vector2D::MeasureAngleBetweenTwoVectors(const Vector2D& other) const
{
    auto dot = Dot(other);
    auto det = Determinant(other);
    return std::atan2(det, dot) * 180 / 3.141592;
}

// double Vector2D::MeasureAngleBetweenTwoVectors(const Vector2D& reference, const Vector2D& other)
// {
//     auto dot = reference.X() * other.X() + reference.Y() * other.Y();
//     auto det = reference.X() * other.Y() - reference.Y() * other.X();
//     return std::atan2(det, dot) * 180 / 3.14;
// }

double Vector2D::Magnitude() const
{
    return _v.norm();
}

void Vector2D::SetMagnitude(double x)
{
    Normalize();
    _v = _v * x;
}

void Vector2D::Normalize()
{
    _v.normalize();
}

void Vector2D::Limit(double max)
{
    double m = Magnitude();

    if(m > max)
    {
        Normalize();
    }
}

double Vector2D::Dot(const Vector2D& other) const
{
    return _v.dot(other._v);
}

double Vector2D::Determinant(const Vector2D& other) const
{
    Eigen::MatrixXd matrix(_v.rows(), other._v.rows());
    matrix << _v, other._v;
    return matrix.determinant();
}
