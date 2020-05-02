#pragma once

#include <random>
#include <type_traits>

#include "boids/exception.hpp"

namespace flocking_simulation
{
    class RandomGenerator
    {
    public:
        template <typename T> static constexpr T Draw(T min, T max) throw(Exception)
        {
            if(!std::is_arithmetic<T>::value)
            {
                throw Exception("Wrong type in random generator.");
            }
            auto distribution = std::uniform_real_distribution<float>(min, max);

            return static_cast<T>(distribution(std::mt19937{std::random_device{}()}));
        };

    private:
        RandomGenerator() = delete;
    };
}