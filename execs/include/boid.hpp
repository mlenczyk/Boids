#pragma once

#include "string"
#include <vector>
#include <SDL.h>
#include "texture.hpp"
#include "vector2d.hpp"

class Boid
{
public:
    Boid(Vector2D position, Vector2D velocity, Texture* boidSmallTexture);
    ~Boid();

    Boid(const Boid& other);

    Boid& operator=(const Boid& other);
    void Free();

    void Update();
    const Texture* GetTexture();

    Vector2D Alignment(std::vector<Boid>& Boids);
    Vector2D Separation(std::vector<Boid>& boids);
    Vector2D ChooseLeader(std::vector<Boid>& boids);

    void ApplyForce(Vector2D force);

    SDL_Rect* clip = nullptr;
    SDL_Point* center = nullptr;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    Vector2D position = {};
    Vector2D velocity = {};
    Vector2D acceleration = {};

    double angle = 0;

private:
    void ChangeOrientation();
    Vector2D PerceiveSurroundingBoidsAndReturnTheirAverageVelocity(std::vector<Boid>& boids);
    Vector2D CalculateAlignmentVelocity(Vector2D averageVelocity);

    Vector2D _absoluteZeroOrientation = {0, -1};
    uint8_t _perception = 20;
    double _maxSpeed = 1;
    double _separationForce = 2;
    Texture* _texture = nullptr;
};