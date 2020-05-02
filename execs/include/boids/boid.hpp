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
        Boid(Vector2D position, Vector2D velocity, const Texture* boidSmallTexture);

        void Update();
        const Texture* GetTexture();

        void Alignment(float distance, Vector2D data);
        Vector2D GetAlignmentImpulse();

        void Cohesion(float distance, Vector2D data);
        Vector2D Boid::GetCohesionImpulse();

        void Separation(float distance, Vector2D data);
        Vector2D Boid::GetSeparationImpulse();

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
        uint16_t _perception = 50;
        uint16_t _alignmentPerception = _perception;
        uint16_t _cohesionPerception = _perception + 50;
        uint16_t _separationPerception = _perception - 20;

        AlignmentSense _alignmentSense = AlignmentSense(_alignmentPerception, velocity);
        CohesionSense _cohesionSense = CohesionSense(_cohesionPerception, position);
        SeparationSense _separationSense = SeparationSense(_separationPerception, position);

        float _maxSpeed = 4;

        const Texture* _texture = nullptr;
    };
}