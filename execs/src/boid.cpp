#include "boid.hpp"
#include <cmath>
#include <cstdio>
#include "SDL_image.h"
#include "vector2d.hpp"

Boid::Boid(SDL_Renderer* renderer, Vector2D pos, Vector2D vel, std::string_view texturePath) :
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
    if(clip != NULL)
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
    SDL_Surface* loadedSurface = IMG_Load(_texturePath.data());
    if(loadedSurface == nullptr)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", _texturePath.data(), IMG_GetError());
    }
    else
    {
        // Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
        if(newTexture == nullptr)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", _texturePath.data(), SDL_GetError());
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
    if(tex != NULL)
    {
        SDL_DestroyTexture(tex);
        tex = NULL;
        width = 0;
        height = 0;
    }
}

void Boid::ChangeOrientation()
{
    auto desiredOrientation = velocity;

    angle = Vector2D::MeasureAngleBetweenTwoVectors(_absoluteZeroOrientation, desiredOrientation);
    // printf("ANGLE: %lf", angle);
}

Vector2D Boid::Steer(Vector2D alignmentVelocity)
{
    return alignmentVelocity - velocity;
}

void Boid::Update()
{
    ChangeOrientation();
    acceleration = acceleration * 0.2;
    velocity += acceleration;
    position += velocity;
    acceleration = Vector2D(); // reset acceleration
}

Vector2D Boid::Align(std::vector<Boid>& boids)
{
    Vector2D alignmentVelocity = {};
    uint8_t closeBoids = 0;
    double distance = 0;
    auto globallyDesiredPosition = Vector2D(600, 600);
    // for(auto& boid: boids)
    // {
    //     distance = DistanceBetweenPoint(position, boid.position);

    //     if(distance < _perception)
    //     {
    //         alignmentVelocity += boid.velocity;
    //         closeBoids++;
    //     }
    // }

    // if(closeBoids > 0)
    // {
    //     printf("alignmentVelocity X: %lf\r\n", alignmentVelocity.X());
    //     printf("alignmentVelocity Y: %lf\r\n", alignmentVelocity.Y());
    //     alignmentVelocity = alignmentVelocity / boids.size();

    //     if(alignmentVelocity > Vector2D(0.01, 0.01))
    //     {
    //         alignmentVelocity = Vector2D(0.01, 0.01);
    //     }

    //     return Steer(alignmentVelocity);
    // }

    // return velocity;
    static constexpr int maxSpeed = 0.0001;

    auto steeringVel = Steer(globallyDesiredPosition);
    if(abs(steeringVel.X()) > abs(maxSpeed))
    {
        if(steeringVel.X() < 0)
        {
            steeringVel.Update(-maxSpeed, velocity.Y());
        }
        else
        {
            // printf("X too high: %lf\r\n", steeringVel.X());
            steeringVel.Update(maxSpeed, velocity.Y());
            // printf("X too high: %lf\r\n", steeringVel.X());
        }
    }
    if(abs(steeringVel.Y()) > abs(maxSpeed))
    {
        if(steeringVel.Y() < 0)
        {
            steeringVel.Update(velocity.X(), -maxSpeed);
        }
        else
        {
            steeringVel.Update(velocity.X(), maxSpeed);
        }
    }

    // distance = Vector2D::MeasureDistanceBetweenTwoVectors(position, globallyDesiredPosition);

    // printf("steeringVel X: %lf\r\n", steeringVel.X());
    // printf("steeringVel Y: %lf\r\n", steeringVel.Y());
    return steeringVel;
}
Vector2D Boid::Alignment(std::vector<Boid>& Boids)
{
    Vector2D sum(0, 0);
    int count = 0;
    for(int i = 0; i < Boids.size(); i++)
    {
        float d = Vector2D::MeasureDistanceBetweenTwoVectors(position, Boids[i].position);
        if((d > 0) && (d < _perception))
        { // 0 < d < 50
            sum + Boids[i].velocity;
            count++;
        }
    }
    // If there are boids close enough for alignment...
    if(count > 0)
    {
        sum = sum / double(count); // Divide sum by the number of close boids (average of velocity)
        sum.Normalize();           // Turn sum into a unit vector, and
        sum = sum * _maxSpeed;     // Multiply by maxSpeed
        // Steer = Desired - Velocity
        Vector2D steer;
        steer = sum - velocity; // sum = desired(average)
        steer.Limit(1);
        return steer;
    }
    else
    {
        Vector2D temp(0, 0);
        return temp;
    }
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