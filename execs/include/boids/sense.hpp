#pragma once

#include <vector>

#include "fwd.hpp"
#include "vector2d.hpp"

namespace flocking_simulation
{
    class AlignmentSense
    {
    public:
        AlignmentSense(float perception, Vector2D velocity);

        void SetVelocity(Vector2D velocity);
        void Perceive(float distance, Vector2D data);
        Vector2D GetImpulse();

    private:
        float _perception;
        Vector2D _velocity;
        uint16_t _perceivedBoidsCount = 0;
        Vector2D _perceivedBoidsVelocitySum = {};
    };

    class CohesionSense
    {
    public:
        CohesionSense(float perception, Vector2D position);

        void SetPosition(Vector2D position);
        void Perceive(float distance, Vector2D data);
        Vector2D GetImpulse();

    private:
        float _perception;
        Vector2D _position;

        uint16_t _perceivedBoidsCount = 0;
        Vector2D _perceivedBoidsPositionSum = {};
    };

    class SeparationSense
    {
    public:
        SeparationSense(float perception, Vector2D position);

        void SetPosition(Vector2D position);
        void Perceive(float distance, Vector2D data);
        Vector2D GetImpulse();

    private:
        float _perception;
        Vector2D _position;

        Vector2D _perceivedBoidsSeparationPosition = {};
    };
}