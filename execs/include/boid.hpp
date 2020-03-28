#pragma once

#include "window.hpp"

class Vector2D
{
public:
    Vector2D() = default;
    Vector2D(double x, double y);

    void Update(double x, double y);
    double X() const;
    double Y() const;

    Vector2D& operator=(const Vector2D& other);
    Vector2D& operator+(const Vector2D& other);
    Vector2D& operator-(const Vector2D& other);
    Vector2D& operator+=(const Vector2D& other);

private:
    double _x;
    double _y;
};

class Boid
{
public:
    Boid(SDL_Renderer* renderer, Vector2D position, Vector2D velocity, std::string_view texturePath);
    ~Boid();

    void Update();
    void Render();

    SDL_Texture* tex = nullptr;
    SDL_Rect* clip = NULL;
    double angle = 0;
    SDL_Point* center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    int width = 10;
    int height = 20;
    Vector2D position;
    Vector2D velocity;

private:
    void Free();
    bool LoadTexture();
    void ChangeOrientation();

    Vector2D _absoluteZeroOrientation = {0, -1};
    SDL_Renderer* _renderer;
    std::string_view _texturePath;
    // double _acceleration;
};