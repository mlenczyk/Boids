#pragma once

#include "string"
#include <vector>
#include <SDL.h>
#include "vector2d.hpp"

class Boid
{
public:
    Boid(SDL_Renderer* renderer, Vector2D position, Vector2D velocity, std::string texturePath);
    ~Boid();

    void Update();
    void Render();
    void SetPosition(Vector2D newPosition);
    Vector2D Align(std::vector<Boid>& boids);
    Vector2D Alignment(std::vector<Boid>& Boids);

    void ApplyForce(Vector2D force);

    SDL_Texture* tex = nullptr;
    SDL_Rect* clip = nullptr;
    SDL_Point* center = nullptr;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    Vector2D position = {};
    Vector2D velocity = {};
    Vector2D acceleration = {};

    int width = 10;
    int height = 17;
    double angle = 0;

private:
    void Free();
    bool LoadTexture();
    void ChangeOrientation();
    Vector2D Steer(Vector2D alignmentVelocity);
    Vector2D PerceiveSurroundingBoidsAndReturnTheirAverageVelocity(std::vector<Boid>& boids);
    Vector2D CalculateAlignmentVelocity(Vector2D averageVelocity);

    Vector2D _absoluteZeroOrientation = {0, -1};
    SDL_Renderer* _renderer = nullptr;
    std::string _texturePath;
    uint8_t _perception = 20;
    double _maxSpeed = 5;
};