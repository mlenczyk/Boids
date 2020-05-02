#include "boids/boid.hpp"
#include "boids/exception.hpp"
#include "boids/vector2d.hpp"

namespace flocking_simulation
{
    Boid::Boid(Vector2D pos, Vector2D vel, const Texture* texture, float maxSpeed) :
        position{pos}, velocity{vel}, _texture{texture}, _maxSpeed{maxSpeed}
    {
    }

    void Boid::ChangeOrientation()
    {
        auto desiredOrientation = velocity;

        angle = _absoluteZeroOrientation.MeasureAngleBetweenTwoVectors(desiredOrientation);
    }

    void Boid::Update()
    {
        velocity += acceleration;
        velocity.SetMagnitude(_maxSpeed);
        position += velocity;

        ChangeOrientation();
        acceleration = Vector2D();
    }

    void Boid::Alignment(float distance, Vector2D data)
    {
        _alignmentSense.SetVelocity(velocity);
        _alignmentSense.Perceive(distance, data);
    }

    Vector2D Boid::GetAlignmentImpulse()
    {
        return _alignmentSense.GetImpulse();
    }

    void Boid::AlignmentReset()
    {
        _alignmentSense.Reset();
    }

    void Boid::Cohesion(float distance, Vector2D data)
    {
        _cohesionSense.SetPosition(position);
        _cohesionSense.Perceive(distance, data);
    }

    Vector2D Boid::GetCohesionImpulse()
    {
        return _cohesionSense.GetImpulse().Limit(_maxSpeed);
    }

    void Boid::CohesionReset()
    {
        _cohesionSense.Reset();
    }

    void Boid::Separation(float distance, Vector2D data)
    {
        _separationSense.SetPosition(position);
        _separationSense.Perceive(distance, data);
    }

    Vector2D Boid::GetSeparationImpulse()
    {
        return _separationSense.GetImpulse().Limit(_maxSpeed);
    }

    void Boid::SeparationReset()
    {
        _separationSense.Reset();
    }

    void Boid::ApplyForce(Vector2D force)
    {
        // F = m * a, but m doesn't matter so F = a
        acceleration += force;
    }

    const Texture* Boid::GetTexture()
    {
        return _texture;
    }

    void Boid::AvoidWallCollision(int width, int height)
    {
        std::vector<Vector2D> walls = {Vector2D(0, position.Y()), //
                                       Vector2D(position.X(), 0),
                                       Vector2D(width, position.Y()),
                                       Vector2D(position.X(), height)};

        for(auto& wall: walls)
        {
            _wallAvoidanceSense.SetPosition(position);
            _wallAvoidanceSense.Perceive(position.MeasureDistanceBetweenTwoVectors(wall), wall);
        }
    }

    Vector2D Boid::GetWallAvoidanceImpulse()
    {
        return _wallAvoidanceSense.GetImpulse().Limit(_maxSpeed);
    }

    void Boid::WallAvoidanceReset()
    {
        _wallAvoidanceSense.Reset();
    }

    void Boid::AvoidObstacleCollision(float distanceToObstacle, Vector2D obstaclePosition)
    {
        _obstacleAvoidanceSense.SetPosition(position);
        _obstacleAvoidanceSense.Perceive(distanceToObstacle, obstaclePosition);
    }

    Vector2D Boid::GetObstacleAvoidanceImpulse()
    {
        return _obstacleAvoidanceSense.GetImpulse().Limit(_maxSpeed);
    }

    void Boid::ObstacleAvoidanceReset()
    {
        _obstacleAvoidanceSense.Reset();
    }

}