#include "boid.hpp"
#include "exception.hpp"
#include "vector2d.hpp"

Boid::Boid(Vector2D pos, Vector2D vel, const Texture& texture) :
    position{pos}, velocity{vel}, _texture{texture}
{
}

void Boid::ChangeOrientation()
{
    auto desiredOrientation = velocity;

    angle = Vector2D::MeasureAngleBetweenTwoVectors(_absoluteZeroOrientation, desiredOrientation);
}

void Boid::Update()
{
    acceleration = acceleration * 10;
    velocity += acceleration;
    velocity.Limit(10);
    // if(velocity.Magnitude() > Vector2D(1, 1).Magnitude())
    // {
    //     throw Exception("WTF SPEED");
    // }
    position += velocity;
    ChangeOrientation();
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

// Vector2D Boid::Separation(std::vector<Boid>& boids)
// {
//     auto separationPosition = Vector2D();
//     double distance = 0;
//     auto separationPerception = 5;
//     for(auto& boid: boids)
//     {
//         distance = Vector2D::MeasureDistanceBetweenTwoVectors(position, boid.position);
//         if((distance > 0) && (distance < separationPerception))
//         {
//             separationPosition = separationPosition - (position - boid.position);
//         }
//     }
//     return separationPosition;
// auto newPosition = Vector2D();
// if(wypadkowa != Vector2D())
// {
//     newPosition = wypadkowa * _separationForce;

//     newPosition = position + wypadkowa;
//     newPosition.Limit(_maxSpeed);
//     return newPosition;
// }
// return wypadkowa;

// auto separationPosition = Vector2D();
// auto wypadkowa = Vector2D();
// double distance = 0;
// for(auto& boid: boids)
// {
//     distance = Vector2D::MeasureDistanceBetweenTwoVectors(position, boid.position);
//     if((distance > 0) && (distance < _perception))
//     {
//         separationPosition = (position - boid.position);
//         wypadkowa += Vector2D(1 / separationPosition.X(), 1 / separationPosition.Y());
//     }
// }
// wypadkowa = wypadkowa * -1;
// // return separationPosition;
// auto newPosition = Vector2D();
// if(wypadkowa != Vector2D())
// {
//     newPosition = wypadkowa * _separationForce;

//     newPosition = position + wypadkowa;
//     newPosition.Limit(_maxSpeed);
//     return newPosition;
// }
// return wypadkowa;

// auto separationPosition = Vector2D();
// double distance = 0;
// for(auto& boid: boids)
// {
//     distance = Vector2D::MeasureDistanceBetweenTwoVectors(position, boid.position);
//     if((distance > 0) && (distance < _perception))
//     {
//         separationPosition += (1 / distance);
//     }
// }

// // return separationPosition;
// auto newPosition = Vector2D();
// if(separationPosition != Vector2D())
// {
//     newPosition = separationPosition * _separationForce;

//     newPosition = separationPosition - position;
//     newPosition.Limit(_maxSpeed);
//     return newPosition;
// }
// return separationPosition;
// }
Vector2D Boid::Separation(std::vector<Boid>& boids)
{
    Vector2D steer(0, 0);
    int count = 0;
    // For every boid in the system, check if it's too close
    for(auto& boid: boids)
    {
        // Calculate distance from current boid to boid we're looking at
        float d = Vector2D::MeasureDistanceBetweenTwoVectors(position, boid.position);
        // If this is a fellow boid and it's too close, move away from it
        if((d > 0) && (d < 20))
        {
            Vector2D diff(0, 0);
            diff = position - boid.position;
            // diff.Normalize();
            diff = diff / (d * d); // Weight by distance
            steer = steer + diff;
            count++;
        }
    }
    // Adds average difference of position to acceleration
    if(count > 0)
    {
        steer = steer / ((float)count);
        steer.SetMagnitude(_maxSpeed);
        steer = steer - velocity;
        steer.Limit(_separationForce);
    }
    return steer;
}

void Boid::ApplyForce(Vector2D force)
{
    // F = m * a // but m doesn't matter so F = a
    acceleration = acceleration + force;
}

const Texture* Boid::GetTexture()
{
    return &_texture;
}
