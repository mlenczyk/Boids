#include "boid.hpp"
#include "string"
#include <cmath>
#include <cstdio>
#include "SDL_image.h"
#include "exception.hpp"
#include "vector2d.hpp"

Boid::Boid(SDL_Renderer* renderer, Vector2D pos, Vector2D vel, std::string texturePath) :
    _renderer{renderer},
    position{pos},
    velocity{vel},
    _texturePath{texturePath}
{
    LoadTexture();
}

Boid::~Boid()
{
    Free();
}

void Boid::Render()
{
    // Set rendering space and render to screen
    SDL_Rect renderQuad = {position.X(), position.Y(), width, height};

    // Set clip rendering dimensions
    if(clip != nullptr)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    // Render to screen
    SDL_RenderCopyEx(_renderer, tex, clip, &renderQuad, angle, center, flip);
}

bool Boid::LoadTexture()
{
    // Get rid of preexisting texture
    Free();
    // The final texture
    SDL_Texture* newTexture = nullptr;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(_texturePath.c_str());
    if(loadedSurface == nullptr)
    {
        throw Exception(
            "Unable to load image " + _texturePath + "! SDL_image Error: " + IMG_GetError() + "\n");
    }
    else
    {
        // Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
        if(newTexture == nullptr)
        {
            throw Exception(
                "Unable to create texture from " + _texturePath + "! SDL Error: " + SDL_GetError() +
                "%s\n");
        }
        else
        {
            // Get image dimensions
            width = loadedSurface->w;
            height = loadedSurface->h;
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    // Return success
    tex = newTexture;
    return tex != nullptr;
}

void Boid::Free()
{
    // Free texture if it exists
    if(tex != nullptr)
    {
        SDL_DestroyTexture(tex);
        tex = nullptr;
        width = 0;
        height = 0;
    }
}

void Boid::ChangeOrientation()
{
    auto desiredOrientation = velocity;

    angle = Vector2D::MeasureAngleBetweenTwoVectors(_absoluteZeroOrientation, desiredOrientation);
}

Vector2D Boid::Steer(Vector2D alignmentVelocity)
{
    return alignmentVelocity - velocity;
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

void Boid::SetPosition(Vector2D newPosition)
{
    position = newPosition;
}

void Boid::ApplyForce(Vector2D force)
{
    // F = m * a // but m doesn't matter so F = a
    acceleration = force;
}