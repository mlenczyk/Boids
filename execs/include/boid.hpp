#pragma once

#include "string"
#include <vector>
#include <SDL.h>
#include "texture.hpp"
#include "vector2d.hpp"

class Boid
{
public:
    Boid(Vector2D position, Vector2D velocity, const Texture& boidSmallTexture);

    void Update();
    const Texture* GetTexture();

    Vector2D Alignment(std::vector<Boid>& Boids);

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
    const std::string _texturePath;
    uint8_t _perception = 20;
    double _maxSpeed = 5;
    const Texture& _texture;
};