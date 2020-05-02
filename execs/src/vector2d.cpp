#include <cmath>

#include "boids/vector2d.hpp"

namespace flocking_simulation
{
    Vector2D::Vector2D(float x, float y) : _v(x, y)
    {
    }

    Vector2D::Vector2D(UnderlyingType v) : _v(v)
    {
    }

    float Vector2D::X() const
    {
        return _v.x();
    }

    float Vector2D::Y() const
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

    Vector2D Vector2D::operator+(float value) const
    {
        return _v + Vector2D(value, value)._v;
    }

    Vector2D Vector2D::operator-(const Vector2D& other) const
    {
        auto v = Vector2D(_v - other._v);
        if(abs(v.X()) < 0.001)
        {
            v = Vector2D(0, v.Y());
        }

        if(abs(v.Y()) < 0.001)
        {
            v = Vector2D(v.X(), 0);
        }
        return v;
    }

    Vector2D Vector2D::operator-(float value) const
    {
        return _v - Vector2D(value, value)._v;
    }

    Vector2D& Vector2D::operator+=(const Vector2D& other)
    {
        _v = _v + other._v;
        return *this;
    }

    Vector2D Vector2D::operator/(float value) const
    {
        auto v = _v / value;
        return Vector2D(v);
    }

    Vector2D Vector2D::operator*(float value) const
    {
        auto v = _v * value;
        return Vector2D(v);
    }

    bool Vector2D::operator!=(const Vector2D& other) const
    {
        return _v != other._v;
    }

    bool Vector2D::operator==(const Vector2D& other) const
    {
        return _v == other._v;
    }

    float Vector2D::MeasureDistanceBetweenTwoVectors(const Vector2D& other) const
    {
        return sqrt(pow(other.X() - _v.x(), 2) + pow(other.Y() - _v.y(), 2));
    }

    float Vector2D::MeasureAngleBetweenTwoVectors(const Vector2D& other) const
    {
        auto dot = Dot(other);
        auto det = Determinant(other);
        return std::atan2(det, dot) * 180 / 3.141592;
    }

    float Vector2D::Magnitude() const
    {
        return _v.norm();
    }

    Vector2D Vector2D::SetMagnitude(float x)
    {
        Normalize();
        _v = _v * x;
        return _v;
    }

    Vector2D Vector2D::Normalize()
    {
        _v.normalize();
        return _v;
    }

    Vector2D Vector2D::Limit(float max)
    {
        float m = Magnitude();

        if(m > max)
        {
            Normalize();
        }

        return _v;
    }

    float Vector2D::Dot(const Vector2D& other) const
    {
        return _v.dot(other._v);
    }

    float Vector2D::Determinant(const Vector2D& other) const
    {
        Eigen::MatrixXd matrix(_v.rows(), other._v.rows());
        matrix << _v, other._v;
        return matrix.determinant();
    }
}