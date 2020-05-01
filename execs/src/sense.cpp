#include "boids/sense.hpp"
#include "boids/boid.hpp"
#include "boids/vector2d.hpp"

namespace flocking_simulation
{
    AlignmentSense::AlignmentSense(float perception, Vector2D position, Vector2D velocity) :
        _perception{perception}, _position{position}, _velocity{velocity}
    {
    }

    void AlignmentSense::SetPosition(Vector2D position)
    {
        _position = position;
    }

    void AlignmentSense::SetVelocity(Vector2D velocity)
    {
        _velocity = velocity;
    }

    Vector2D AlignmentSense::Perceive(const std::vector<Boid>& boids) const
    {
        uint16_t perceivedBoidsCount = 0;
        auto alignmentVelocity = Vector2D();
        float distance = 0;
        for(auto& boid: boids)
        {
            distance = _position.MeasureDistanceBetweenTwoVectors(boid.position);
            if(distance < _perception)
            {
                alignmentVelocity += boid.velocity;
                perceivedBoidsCount++;
            }
        }

        if(perceivedBoidsCount > 0)
        {
            alignmentVelocity = alignmentVelocity / float(perceivedBoidsCount);
        }

        return alignmentVelocity - _velocity;
    }

    CohesionSense::CohesionSense(float perception, Vector2D position) :
        _perception{perception}, _position{position}
    {
    }

    void CohesionSense::SetPosition(Vector2D position)
    {
        _position = position;
    }

    Vector2D CohesionSense::Perceive(const std::vector<Boid>& boids) const
    {
        uint16_t perceivedBoidsCount = 0;
        auto averagePosition = Vector2D();
        float distance = 0;
        for(auto& boid: boids)
        {
            distance = _position.Vector2D::MeasureDistanceBetweenTwoVectors(boid.position);
            if(distance < _perception)
            {
                averagePosition += boid.position;
                perceivedBoidsCount++;
            }
        }

        if(perceivedBoidsCount > 0)
        {
            averagePosition = averagePosition / float(perceivedBoidsCount);
        }

        return averagePosition - _position;
    }

    SeparationSense::SeparationSense(float perception, Vector2D position) :
        _perception{perception}, _position{position}
    {
    }

    void SeparationSense::SetPosition(Vector2D position)
    {
        _position = position;
    }

    Vector2D SeparationSense::Perceive(const std::vector<Boid>& boids) const
    {
        auto positionDifference = Vector2D();
        auto separationVelocity = Vector2D();
        float distance = 0;
        for(auto& boid: boids)
        {
            distance = _position.MeasureDistanceBetweenTwoVectors(boid.position);
            if(distance < _perception)
            {
                positionDifference = _position - boid.position;

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

                separationVelocity += Vector2D(x, y);
            }
        }
        return separationVelocity;
    }
}