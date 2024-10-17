#pragma once
#include <SFML/System/Vector2.hpp>
#include <concepts>
#include <numbers>
#include <random>

float getLength(const sf::Vector2f& vec);
sf::Vector2f truncate(const sf::Vector2f& vec, float max); 
sf::Vector2f normalize(const sf::Vector2f& source);
float toRadians(float angle);
float toDegrees(float radians);
sf::Vector2f setAngle(sf::Vector2f& vector, float angle);
float computeTargetAngle(const sf::Vector2f& vector);
float distance(const sf::Vector2f& obj1, const sf::Vector2f& obj2);

template <std::integral T>
sf::Vector2f& operator*=(sf::Vector2f& lhs, T val)
{
    lhs.x *= val;
    lhs.y *= val;
    return lhs;
}

template <std::integral T>
sf::Vector2f& operator*(sf::Vector2f& lhs, T val)
{
    return lhs *= val;
}

float randomFloat(float min, float max);

template <std::floating_point T>
inline bool isNearlyEqual(T x, T y);

template<std::floating_point T>
inline bool isNearlyEqual(T x, T y)
{
    const T epsilon = 0.000001;
    return std::abs(x - y) <= epsilon * std::abs(x);
}
