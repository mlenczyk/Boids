#include <vector>

#include "boids/boid.hpp"
#include "boids/flock.hpp"
#include "boids/randomGenerator.hpp"
#include "boids/vector2d.hpp"

namespace flocking_simulation
{
    Flock::Flock(int boidsCount, std::string texturePath, Window* window) :
        _boidsCount{boidsCount}, _boidsTexture{window->LoadTexture(texturePath)}, _window{window}
    {
        Initialize();
    }

    void Flock::Initialize()
    {
        static constexpr float VelocityMin = -1.5;
        static constexpr float VelocityMax = 1.5;
        static constexpr float MaxSpeed = 6;

        for(auto i = 0; i < _boidsCount; i++)
        {
            _boids.push_back(Boid(
                Vector2D(
                    RandomGenerator::Draw(21, _window->GetWidth() - 21),
                    RandomGenerator::Draw(21, _window->GetHeight() - 21)),
                Vector2D(
                    RandomGenerator::Draw(VelocityMin, VelocityMax),
                    RandomGenerator::Draw(VelocityMin, VelocityMax)),
                &_boidsTexture,
                MaxSpeed));
        }
        _boidsSnapshot = _boids;
    }

    void Flock::Run()
    {
        while(!_window->IsClosed())
        {
            auto loopBeginning = SDL_GetTicks();
            _window->PollEvents();

            auto beforeBoidIter = SDL_GetTicks();
            for(int i = 0; i < _boids.size(); i++)
            {
                _boids[i].AlignmentReset();
                _boids[i].CohesionReset();
                _boids[i].SeparationReset();
                _boids[i].WallAvoidanceReset();
                _boids[i].ObstacleAvoidanceReset();

                for(auto& boid: _boids)
                {
                    auto distance = _boids[i].position.MeasureDistanceBetweenTwoVectors(boid.position);

                    _boids[i].Alignment(distance, boid.velocity);
                    _boids[i].Cohesion(distance, boid.position);
                    _boids[i].Separation(distance, boid.position);
                }
                _boids[i].AvoidWallCollision(_window->GetWidth(), _window->GetHeight());
                for(auto& obstacle: *(_window->GetObstacles()))
                {
                    auto obstacleV = Vector2D(obstacle.x, obstacle.y);
                    auto obstacleDistance =
                        _boids[i].position.MeasureDistanceBetweenTwoVectors(obstacleV);
                    _boids[i].AvoidObstacleCollision(obstacleDistance, obstacleV);
                }

                auto forceOfAlignment = _boids[i].GetAlignmentImpulse();
                auto forceOfCohesion = _boids[i].GetCohesionImpulse();
                auto forceOfSeparation = _boids[i].GetSeparationImpulse();
                auto forceOfWallAvoidance = _boids[i].GetWallAvoidanceImpulse();
                auto forceOfObstacleAvoidance = _boids[i].GetObstacleAvoidanceImpulse();

                forceOfAlignment = forceOfAlignment * 0.5;
                forceOfCohesion = forceOfCohesion * 0.3;
                forceOfSeparation = forceOfSeparation * 1.6;
                forceOfWallAvoidance = forceOfWallAvoidance * 100;
                forceOfObstacleAvoidance = forceOfObstacleAvoidance * 15;

                _boidsSnapshot[i].ApplyForce(forceOfAlignment);
                _boidsSnapshot[i].ApplyForce(forceOfCohesion);
                _boidsSnapshot[i].ApplyForce(forceOfSeparation);
                _boidsSnapshot[i].ApplyForce(forceOfWallAvoidance);
                _boidsSnapshot[i].ApplyForce(forceOfObstacleAvoidance);

                _boidsSnapshot[i].Update();

                _window->KeepBoidInScreen(_boidsSnapshot[i]);
                _window->Render(_boidsSnapshot[i]);
            }

            auto beforeUpdateWindow = SDL_GetTicks();
            _window->UpdateWindow();

            _boids = _boidsSnapshot;

            auto endOfLoop = SDL_GetTicks();
            printf("__________________\r\n");
            printf("pollEvents: %d\r\n", beforeBoidIter - loopBeginning);
            printf("boidIter: %d\r\n", beforeUpdateWindow - beforeBoidIter);
            printf("windowUpdate: %d\r\n", endOfLoop - beforeUpdateWindow);
        }
    }
}