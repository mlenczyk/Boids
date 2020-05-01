#pragma once

#include "string"
#include <vector>
#include <SDL.h>

#include "sense.hpp"
#include "texture.hpp"
#include "vector2d.hpp"

namespace flocking_simulation
{
    class Boid
    {
    public:
        Boid(Vector2D position, Vector2D velocity, Texture* boidSmallTexture);

        void Update();
        const Texture* GetTexture();

        Vector2D Alignment(const std::vector<Boid>& Boids);
        Vector2D Separation(const std::vector<Boid>& boids);
        Vector2D Cohesion(const std::vector<Boid>& boids);

        void ApplyForce(Vector2D force);

        SDL_Rect clip = {};
        SDL_Point center = {};
        SDL_RendererFlip flip = SDL_FLIP_NONE;

        Vector2D position = {};
        Vector2D velocity = {};
        Vector2D acceleration = {};

        float angle = 0;

    private:
        void ChangeOrientation();

        Vector2D _absoluteZeroOrientation = {0, -1};

        // probably want to make this one variable some day
        uint16_t _perception = 60;
        uint16_t _alignmentPerception = _perception;
        uint16_t _cohesionPerception = _perception + 100;
        uint16_t _separationPerception = _perception - 40;

        AlignmentSense _alignmentSense = AlignmentSense(_alignmentPerception, position, velocity);
        CohesionSense _cohesionSense = CohesionSense(_cohesionPerception, position);
        SeparationSense _separationSense = SeparationSense(_separationPerception, position);

        float _maxSpeed = 4;

        Texture* _texture = nullptr;
    };
}