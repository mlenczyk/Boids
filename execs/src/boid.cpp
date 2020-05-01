#include "boids/boid.hpp"
#include "boids/exception.hpp"
#include "boids/vector2d.hpp"

namespace flocking_simulation
{
    Boid::Boid(Vector2D pos, Vector2D vel, Texture* texture) :
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

    Vector2D Boid::Alignment(const std::vector<Boid>& boids)
    {
        _alignmentSense.SetPosition(position);
        _alignmentSense.SetVelocity(velocity);
        return _alignmentSense.Perceive(boids);
    }

    Vector2D Boid::Cohesion(const std::vector<Boid>& boids)
    {
        _cohesionSense.SetPosition(position);
        return _cohesionSense.Perceive(boids).Limit(_maxSpeed);
    }

    Vector2D Boid::Separation(const std::vector<Boid>& boids)
    {
        _separationSense.SetPosition(position);
        return _separationSense.Perceive(boids).Limit(_maxSpeed);
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