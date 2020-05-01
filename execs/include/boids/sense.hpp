#pragma once

#include <vector>

#include "fwd.hpp"
#include "vector2d.hpp"

namespace flocking_simulation
{
    class ISense
    {
    public:
        virtual void SetPosition(Vector2D position) = 0;
        virtual Vector2D Perceive(const std::vector<Boid>& boids) const = 0;

    protected:
        virtual ~ISense() = default;
    };

    class AlignmentSense : public ISense
    {
    public:
        AlignmentSense(float perception, Vector2D position, Vector2D velocity);
        void SetPosition(Vector2D position) override;
        void SetVelocity(Vector2D velocity);
        Vector2D Perceive(const std::vector<Boid>& boids) const override;

    private:
        float _perception;
        Vector2D _position;
        Vector2D _velocity;
    };

    class CohesionSense : public ISense
    {
    public:
        CohesionSense(float perception, Vector2D position);
        void SetPosition(Vector2D position) override;
        Vector2D Perceive(const std::vector<Boid>& boids) const override;

    private:
        float _perception;
        Vector2D _position;
    };

    class SeparationSense : public ISense
    {
    public:
        SeparationSense(float perception, Vector2D position);
        void SetPosition(Vector2D position) override;
        Vector2D Perceive(const std::vector<Boid>& boids) const override;

    private:
        float _perception;
        Vector2D _position;
    };
}