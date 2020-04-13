#include "boids/boid.hpp"
#include "boids/exception.hpp"
#include "boids/vector2d.hpp"

namespace flocking_simulation
{
    Boid::Boid(Vector2D pos, Vector2D vel, Texture* texture) :
        position{pos}, velocity{vel}, _texture{texture}
    {
    }

    // Boid::~Boid()
    // {
    //     Free();
    // }

    // Boid::Boid(const Boid& other)
    // {
    //     clip = other.clip;
    //     center = other.center;
    //     flip = other.flip;
    //     position = other.position;
    //     velocity = other.velocity;
    //     acceleration = other.acceleration;
    //     angle = other.angle;
    //     _texture = other._texture;
    // }

    // Boid& Boid::operator=(const Boid& other)
    // {
    //     if(this != &other)
    //     {
    //         Free();
    //         clip = other.clip;
    //         center = other.center;
    //         flip = other.flip;
    //         position = other.position;
    //         velocity = other.velocity;
    //         acceleration = other.acceleration;
    //         angle = other.angle;
    //         _texture = other._texture;
    //     }
    //     return *this;
    // }

    // void Boid::Free()
    // {
    //     clip = {};
    //     center = {};
    //     flip = SDL_FLIP_NONE;
    //     position = Vector2D();
    //     velocity = Vector2D();
    //     acceleration = Vector2D();
    //     angle = 0;
    //     _texture = nullptr;
    // }

    void Boid::ChangeOrientation()
    {
        auto desiredOrientation = velocity;

        angle = _absoluteZeroOrientation.MeasureAngleBetweenTwoVectors(desiredOrientation);
    }

    void Boid::Update()
    {
        acceleration = acceleration * 0.2;
        velocity += acceleration;
        velocity.Limit(_maxSpeed);
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
            distance = position.MeasureDistanceBetweenTwoVectors(boid.position);
            if((&boid != this) && (distance < _alignmentPerception))
            {
                alignmentVelocity += boid.velocity;
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

    Vector2D Boid::Separation(const std::vector<Boid>& boids) const
    {
        auto separationPosition = Vector2D();
        auto wypadkowa = Vector2D();
        double distance = 0;
        for(auto& boid: boids)
        {
            distance = position.MeasureDistanceBetweenTwoVectors(boid.position);
            if((&boid != this) && (distance < _separationPerception))
            {
                separationPosition = (position - boid.position);
                if(abs(separationPosition.X()) < 0.1 || abs(separationPosition.Y()) < 0.5)
                {
                    continue;
                }
                else
                {
                    wypadkowa += Vector2D(1 / separationPosition.X(), 1 / separationPosition.Y());
                }

                if(separationPosition.X() == 0 || separationPosition.Y() == 0)
                {
                    throw Exception("Zero division in separation");
                }
            }
        }

        auto newPosition = Vector2D();
        if(wypadkowa != Vector2D())
        {
            newPosition = position - wypadkowa;
            newPosition.Limit(_maxSpeed);
            return newPosition;
        }
        return wypadkowa;
    }

    Vector2D Boid::Cohesion(std::vector<Boid>& boids)
    {
        uint16_t perceivedBoidsCount = 0;
        auto averagePosition = Vector2D();
        double distance = 0;
        for(auto& boid: boids)
        {
            distance = position.Vector2D::MeasureDistanceBetweenTwoVectors(boid.position);
            if((&boid != this) && (distance < _cohesionPerception))
            {
                averagePosition += boid.position;
                perceivedBoidsCount++;
            }
        }
        auto cohesionPosition = Vector2D();
        if(perceivedBoidsCount > 0)
        {
            cohesionPosition = averagePosition / double(perceivedBoidsCount);

            cohesionPosition = cohesionPosition - position;
            cohesionPosition.Limit(_maxSpeed);
            return cohesionPosition;
        }
        return cohesionPosition;
    }

    void Boid::ApplyForce(Vector2D force)
    {
        // F = m * a // but m doesn't matter so F = a
        acceleration = acceleration + force;
    }

    const Texture* Boid::GetTexture()
    {
        return _texture;
    }
}