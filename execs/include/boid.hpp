#pragma once

#include <string_view>
#include <vector>
#include <SDL.h>
#include "vector2d.hpp"

class Boid
{
public:
    Boid(SDL_Renderer* renderer, Vector2D position, Vector2D velocity, std::string_view texturePath);
    ~Boid();

    void Update();
    void Render();
    void SetPosition(Vector2D newPosition);
    Vector2D Align(std::vector<Boid>& boids);
    Vector2D Alignment(std::vector<Boid>& Boids);

    void ApplyForce(Vector2D force);

    SDL_Texture* tex = nullptr;
    SDL_Rect* clip = NULL;
    SDL_Point* center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    Vector2D position = {};
    Vector2D velocity = {};
    Vector2D acceleration = {};

    int width = 10;
    int height = 20;
    double angle = 0;

private:
    void Free();
    bool LoadTexture();
    void ChangeOrientation();
    Vector2D Steer(Vector2D alignmentVelocity);

    Vector2D _absoluteZeroOrientation = {0, -1};
    SDL_Renderer* _renderer = nullptr;
    std::string_view _texturePath = {};
    uint8_t _perception = 20;
    double _maxSpeed = 3;
};