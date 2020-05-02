#include "boids/sense.hpp"
#include "boids/boid.hpp"
#include "boids/vector2d.hpp"

namespace flocking_simulation
{
    AlignmentSense::AlignmentSense(float perception, Vector2D velocity) :
        _perception{perception}, _velocity{velocity}
    {
    }

    void AlignmentSense::SetVelocity(Vector2D velocity)
    {
        _velocity = velocity;
    }

    void AlignmentSense::Reset()
    {
        _perceivedBoidsVelocitySum = Vector2D();
        _perceivedBoidsCount = 0;
    }

    void AlignmentSense::Perceive(float distance, Vector2D data)
    {
        if(distance < _perception)
        {
            _perceivedBoidsVelocitySum += data;
            _perceivedBoidsCount++;
        }
    }

    Vector2D AlignmentSense::GetImpulse()
    {
        if(_perceivedBoidsCount <= 0)
        {
            return Vector2D();
        }

        return (_perceivedBoidsVelocitySum / float(_perceivedBoidsCount)) - _velocity;
    }

    CohesionSense::CohesionSense(float perception, Vector2D position) :
        _perception{perception}, _position{position}
    {
    }

    void CohesionSense::SetPosition(Vector2D position)
    {
        _position = position;
    }

    void CohesionSense::Reset()
    {
        _perceivedBoidsPositionSum = Vector2D();
        _perceivedBoidsCount = 0;
    }

    void CohesionSense::Perceive(float distance, Vector2D data)
    {
        if(distance < _perception)
        {
            _perceivedBoidsPositionSum += data;
            _perceivedBoidsCount++;
        }
    }

    Vector2D CohesionSense::GetImpulse()
    {
        if(_perceivedBoidsCount <= 0)
        {
            return Vector2D();
        }

        return (_perceivedBoidsPositionSum / float(_perceivedBoidsCount)) - _position;
    }

    SeparationSense::SeparationSense(float perception, Vector2D position) :
        _perception{perception}, _position{position}
    {
    }

    void SeparationSense::SetPosition(Vector2D position)
    {
        _position = position;
    }

    void SeparationSense::Reset()
    {
        _perceivedBoidsSeparationPosition = Vector2D();
    }

    void SeparationSense::Perceive(float distance, Vector2D data)
    {
        if(distance < _perception)
        {
            auto positionDifference = _position - data;

            float x = 0;
            if(positionDifference.X() != 0)
            {
                x = 1 / positionDifference.X();
            }

            float y = 0;
            if(positionDifference.Y() != 0)
            {
                y = 1 / positionDifference.Y();
            }

            _perceivedBoidsSeparationPosition += Vector2D(x, y);
        }
    }

    Vector2D SeparationSense::GetImpulse()
    {
        return _perceivedBoidsSeparationPosition;
    }
}