#include "boid.hpp"
#include "exception.hpp"
#include "vector2d.hpp"

Boid::Boid(Vector2D pos, Vector2D vel, Texture* texture) :
    position{pos}, velocity{vel}, _texture{texture}
{
}

Boid::~Boid()
{
    Free();
}

Boid::Boid(const Boid& other)
{
    clip = other.clip;
    center = other.center;
    flip = other.flip;
    position = other.position;
    velocity = other.velocity;
    acceleration = other.acceleration;
    angle = other.angle;
    _texture = other._texture;
}

Boid& Boid::operator=(const Boid& other)
{
    if(this != &other)
    {
        Free();
        clip = other.clip;
        center = other.center;
        flip = other.flip;
        position = other.position;
        velocity = other.velocity;
        acceleration = other.acceleration;
        angle = other.angle;
        _texture = other._texture;
    }
    return *this;
}

void Boid::Free()
{
    clip = nullptr;
    center = nullptr;
    flip = SDL_FLIP_NONE;
    position = Vector2D();
    velocity = Vector2D();
    acceleration = Vector2D();
    angle = 0;
    _texture = nullptr;
}

void Boid::ChangeOrientation()
{
    auto desiredOrientation = velocity;

    angle = Vector2D::MeasureAngleBetweenTwoVectors(_absoluteZeroOrientation, desiredOrientation);
}

void Boid::Update()
{
    acceleration = acceleration * 0.4;
    velocity += acceleration;
    velocity.Limit(_maxSpeed);
    // if(velocity.Magnitude() > Vector2D(1, 1).Magnitude())
    // {
    //     throw Exception("WTF SPEED");
    // }
    position += velocity;
    ChangeOrientation();
    acceleration = Vector2D();
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

Vector2D Boid::ChooseLeader(std::vector<Boid>& boids)
{
    auto separationPosition = Vector2D();
    double distance = 0;
    auto separationPerception = 20;
    for(auto& boid: boids)
    {
        distance = Vector2D::MeasureDistanceBetweenTwoVectors(position, boid.position);
        if((distance > 0) && (distance < separationPerception))
        {
            separationPosition = separationPosition - (position - boid.position);
        }
    }
    // return separationPosition;
    if(separationPosition != Vector2D())
    {
        separationPosition = separationPosition * _separationForce;

        separationPosition = position + separationPosition;
        separationPosition.Limit(_maxSpeed);
    }
    return separationPosition;
}
Vector2D Boid::Separation(std::vector<Boid>& boids)
{
    auto separationPosition = Vector2D();
    double distance = 0;
    auto separationPerception = 100;
    for(auto& boid: boids)
    {
        distance = Vector2D::MeasureDistanceBetweenTwoVectors(position, boid.position);
        if((distance > 0) && (distance < separationPerception))
        {
            separationPosition = separationPosition - (position - boid.position);
        }
    }
    // return separationPosition;
    if(separationPosition != Vector2D())
    {
        separationPosition = separationPosition * _separationForce;

        separationPosition = position + separationPosition;
        separationPosition.Limit(_maxSpeed);
    }
    return separationPosition;
}

// auto separationPosition = Vector2D();
// auto wypadkowa = Vector2D();
// double distance = 0;
// for(auto& boid: boids)
// {
//     distance = Vector2D::MeasureDistanceBetweenTwoVectors(position, boid.position);
//     if((distance > 0) && (distance < 30))
//     {
//         separationPosition = (position - boid.position);
//         wypadkowa += Vector2D(1 / separationPosition.X(), 1 / separationPosition.Y());
//     }
// }

// auto newPosition = Vector2D();
// if(wypadkowa != Vector2D())
// {
//     newPosition = position - wypadkowa;
//     newPosition.Limit(_maxSpeed);
//     return newPosition;
// }
// // return wypadkowa;
// }

// Vector2D Boid::Separation(std::vector<Boid>& boids)
// {
//     Vector2D steer(0, 0);
//     int count = 0;
//     // For every boid in the system, check if it's too close
//     for(auto& boid: boids)
//     {
//         // Calculate distance from current boid to boid we're looking at
//         float d = Vector2D::MeasureDistanceBetweenTwoVectors(position, boid.position);
//         // If this is a fellow boid and it's too close, move away from it
//         if((d > 0) && (d < 10))
//         {
//             Vector2D diff(0, 0);
//             diff = position - boid.position;
//             // diff.Normalize();
//             diff = diff / (d * d); // Weight by distance
//             steer = steer + diff;
//             count++;
//         }
//     }
//     // Adds average difference of position to acceleration
//     if(count > 0)
//     {
//         steer = steer / ((float)count);
//         steer.SetMagnitude(_maxSpeed);
//         steer = steer - velocity;
//         steer.Limit(_separationForce);
//     }
//     return steer;
// }

void Boid::ApplyForce(Vector2D force)
{
    // F = m * a // but m doesn't matter so F = a
    acceleration = acceleration + force;
}

const Texture* Boid::GetTexture()
{
    return _texture;
}
