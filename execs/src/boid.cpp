#include "boid.hpp"
#include <cmath>
#include <cstdio>
#include "SDL_image.h"

Vector2D::Vector2D(double x, double y) : _x(x), _y(y)
{
}
void Vector2D::Update(double x, double y)
{
    _x = x;
    _y = y;
}

double Vector2D::X() const
{
    return _x;
}
double Vector2D::Y() const
{
    return _y;
}

Vector2D& Vector2D::operator=(const Vector2D& other)
{
    _x = other.X();
    _y = other.Y();
    return *this;
}

Vector2D& Vector2D::operator+(const Vector2D& other)
{
    _x = _x + other.X();
    _y = _y + other.Y();
    return *this;
}

Vector2D& Vector2D::operator-(const Vector2D& other)
{
    _x = _x - other.X();
    _y = _y - other.Y();
    return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D& other)
{
    return operator+(other);
}

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

Boid::Boid(SDL_Renderer* renderer, Vector2D position, Vector2D velocity, std::string_view texturePath) :
    _renderer(renderer),
    position(position),
    velocity(velocity),
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

    auto dot = _absoluteZeroOrientation.X() * desiredOrientation.X() +
        _absoluteZeroOrientation.Y() * desiredOrientation.Y();
    auto det = _absoluteZeroOrientation.X() * desiredOrientation.Y() -
        _absoluteZeroOrientation.Y() * desiredOrientation.X();
    angle = std::atan2(det, dot) * 180 / M_PI;
    // printf("ANGLE: %lf", angle);
}

void Boid::Update()
{
    ChangeOrientation();
    position = position + velocity;
}
