#include "boid.hpp"
#include "exception.hpp"
#include "vector2d.hpp"

Boid::Boid(Vector2D pos, Vector2D vel, const Texture& texture) :
    position{pos},
    velocity{vel},
    _texture{texture}
{
}

void Boid::ChangeOrientation()
{
    auto desiredOrientation = velocity;

    angle = Vector2D::MeasureAngleBetweenTwoVectors(_absoluteZeroOrientation, desiredOrientation);
}

void Boid::Update()
{
    ChangeOrientation();
    acceleration = acceleration * 0.8;
    velocity += acceleration;
    position += velocity;
    ApplyForce(Vector2D());
}

Vector2D Boid::PerceiveSurroundingBoidsAndReturnTheirAverageVelocity(std::vector<Boid>& boids)
{
    uint16_t perceivedBoidsCount = 0;
    Vector2D alignmentVelocity(0, 0);
    double distance = 0;
    for(auto& boid: boids)
    {
        distance = Vector2D::MeasureDistanceBetweenTwoVectors(position, boid.position);
        if((distance > 0) && (distance < _perception))
        {
            alignmentVelocity + boid.velocity;
            perceivedBoidsCount++;
        }
    }

    if(perceivedBoidsCount > 0)
    {
        alignmentVelocity = alignmentVelocity / double(perceivedBoidsCount);
        return alignmentVelocity;
    }
    else
    {
        return Vector2D();
    }
}

Vector2D Boid::CalculateAlignmentVelocity(Vector2D averageVelocity)
{
    if(averageVelocity != Vector2D())
    {
        averageVelocity.Normalize();
        averageVelocity = averageVelocity * _maxSpeed;

        Vector2D alignmentVelocity;
        alignmentVelocity = averageVelocity - velocity;
        alignmentVelocity.Limit(_maxSpeed);
        return alignmentVelocity;
    }
    return averageVelocity;
}

Vector2D Boid::Alignment(std::vector<Boid>& boids)
{
    auto averageVelocity = PerceiveSurroundingBoidsAndReturnTheirAverageVelocity(boids);
    return CalculateAlignmentVelocity(averageVelocity);
}

void Boid::ApplyForce(Vector2D force)
{
    // F = m * a // but m doesn't matter so F = a
    acceleration = force;
}

const Texture* Boid::GetTexture()
{
    return &_texture;
}
