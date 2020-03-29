#include "vector2d.hpp"
#include <cmath>

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

Vector2D& Vector2D::operator+(const Vector2D& other)
{
    _x = _x + other.X();
    _y = _y + other.Y();
    return *this;
}

Vector2D& Vector2D::operator+(double value)
{
    _x = _x + value;
    _y = _y + value;
    return *this;
}

Vector2D& Vector2D::operator-(const Vector2D& other)
{
    _x = _x - other.X();
    _y = _y - other.Y();
    return *this;
}
Vector2D& Vector2D::operator-(double value)
{
    _x = _x - value;
    _y = _y - value;
    return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D& other)
{
    return operator+(other);
}

Vector2D& Vector2D::operator/(const Vector2D& other)
{
    _x = _x / other.X();
    _y = _y / other.Y();
    return *this;
}

Vector2D& Vector2D::operator/(double value)
{
    _x = _x / value;
    _y = _y / value;
    return *this;
}

Vector2D& Vector2D::operator*(const Vector2D& other)
{
    _x = _x * other.X();
    _y = _y * other.Y();
    return *this;
}

Vector2D& Vector2D::operator*(double value)
{
    _x = _x * value;
    _y = _y * value;
    return *this;
}

bool Vector2D::operator<(const Vector2D& other)
{
    return _x < other.X() && _y < other.Y();
}

bool Vector2D::operator>(const Vector2D& other)
{
    return _x > other.X() && _y > other.Y();
}

bool Vector2D::operator!=(const Vector2D& other)
{
    return _x != other.X() && _y != other.Y();
}

Vector2D Vector2D::AddTwoVectors(const Vector2D& a, const Vector2D& b)
{
    return Vector2D(a.X() + b.X(), a.Y() + b.Y());
}

double Vector2D::MeasureDistanceBetweenTwoVectors(const Vector2D& reference, const Vector2D& other)
{
    return sqrt(pow(other.X() - reference.X(), 2) + pow(other.Y() - reference.Y(), 2));
}

double Vector2D::MeasureAngleBetweenTwoVectors(const Vector2D& reference, const Vector2D& other)
{
    auto dot = reference.X() * other.X() + reference.Y() * other.Y();
    auto det = reference.X() * other.Y() - reference.Y() * other.X();
    return std::atan2(det, dot) * 180 / M_PI;
}

double Vector2D::Magnitude()
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