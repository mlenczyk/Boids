#include "boids/boid.hpp"
#include "boids/exception.hpp"
#include "boids/vector2d.hpp"

namespace flocking_simulation
{
    Boid::Boid(Vector2D pos, Vector2D vel, const Texture* texture) :
        position{pos}, velocity{vel}, _texture{texture}
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

    void Boid::Cohesion(float distance, Vector2D data)
    {
        _cohesionSense.SetPosition(position);
        _cohesionSense.Perceive(distance, data);
    }

    Vector2D Boid::GetCohesionImpulse()
    {
        return _cohesionSense.GetImpulse().Limit(_maxSpeed);
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

    void Boid::ApplyForce(Vector2D force)
    {
        // F = m * a, but m doesn't matter so F = a
        acceleration += force;
    }

    const Texture* Boid::GetTexture()
    {
        return _texture;
    }
}