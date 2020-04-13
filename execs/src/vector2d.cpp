#include <cmath>

#include "boids/exception.hpp"
#include "boids/vector2d.hpp"

Vector2D::Vector2D(double x, double y) : _x(x), _y(y)
{
}

void Vector2D::Update(double x, double y)
{
    _x = x;
    _y = y;
}

double Vector2D::X() const
{
    return _x;
}

double Vector2D::Y() const
{
    return _y;
}

Vector2D& Vector2D::operator=(const Vector2D& other)
{
    _x = other.X();
    _y = other.Y();
    return *this;
}

Vector2D Vector2D::operator+(const Vector2D& other) const
{
    auto x = _x + other.X();
    auto y = _y + other.Y();
    return Vector2D(x, y);
}

Vector2D Vector2D::operator+(double value) const
{
    auto x = _x + value;
    auto y = _y + value;
    return Vector2D(x, y);
}

Vector2D Vector2D::operator-(const Vector2D& other) const
{
    auto x = _x - other.X();
    auto y = _y - other.Y();
    return Vector2D(x, y);
}
Vector2D Vector2D::operator-(double value) const
{
    auto x = _x - value;
    auto y = _y - value;
    return Vector2D(x, y);
}

Vector2D& Vector2D::operator+=(const Vector2D& other)
{
    _x = _x + other.X();
    _y = _y + other.Y();
    return *this;
}

Vector2D Vector2D::operator/(const Vector2D& other) const
{
    if(other.X() == 0 || other.Y() == 0)
    {
        throw Exception("Zero division in vector");
    }
    auto x = _x / other.X();
    auto y = _y / other.Y();
    return Vector2D(x, y);
}

Vector2D Vector2D::operator/(double value) const
{
    if(value == 0)
    {
        throw Exception("Zero division in vector");
    }
    auto x = _x / value;
    auto y = _y / value;
    return Vector2D(x, y);
}

Vector2D Vector2D::operator*(const Vector2D& other) const
{
    auto x = _x * other.X();
    auto y = _y * other.Y();
    return Vector2D(x, y);
}

Vector2D Vector2D::operator*(double value) const
{
    auto x = _x * value;
    auto y = _y * value;
    return Vector2D(x, y);
}

bool Vector2D::operator<(const Vector2D& other) const
{
    return _x < other.X() && _y < other.Y();
}

bool Vector2D::operator>(const Vector2D& other) const
{
    return _x > other.X() && _y > other.Y();
}

bool Vector2D::operator!=(const Vector2D& other) const
{
    return _x != other.X() && _y != other.Y();
}

// Vector2D operator+(const Vector2D& a, const Vector2D& b)const
// {
//     return Vector2D(a.X() + b.X(), a.Y() + b.Y());
// }

double Vector2D::MeasureDistanceBetweenTwoVectors(const Vector2D& reference, const Vector2D& other)
{
    return sqrt(pow(other.X() - reference.X(), 2) + pow(other.Y() - reference.Y(), 2));
}

double Vector2D::MeasureAngleBetweenTwoVectors(const Vector2D& reference, const Vector2D& other)
{
    auto dot = reference.X() * other.X() + reference.Y() * other.Y();
    auto det = reference.X() * other.Y() - reference.Y() * other.X();
    return std::atan2(det, dot) * 180 / 3.14;
}

double Vector2D::Magnitude() const
{
    return sqrt(_x * _x + _y * _y);
}

void Vector2D::SetMagnitude(double x)
{
    Normalize();
    (*this) * x;
}

void Vector2D::Normalize()
{
    double m = Magnitude();

    if(m > 0)
    {
        Update(_x / m, _y / m);
    }
    else
    {
        Update(_x, _y);
    }
}

void Vector2D::Limit(double max)
{
    double size = Magnitude();

    if(size > max)
    {
        Update(_x / size, _y / size);
    }
}