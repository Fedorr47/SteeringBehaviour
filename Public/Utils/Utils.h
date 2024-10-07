#pragma once
#include <SFML/System/Vector2.hpp>
#include <concepts>
#include <numbers>

float getLength(const sf::Vector2f& vec);
sf::Vector2f truncate(const sf::Vector2f& vec, float max); 
sf::Vector2f normalize(const sf::Vector2f& source);
float toRadians(float angle);
float toDegrees(float radians);
sf::Vector2f setAngle(sf::Vector2f& vector, float angle);
float computeTargetAngle(const sf::Vector2f& vector);

template <std::integral T>
sf::Vector2f& operator*=(sf::Vector2f& lhs, T val)
{
    lhs.x *= val;
    lhs.y *= val;
    return lhs;
}

template <std::integral T>
sf::Vector2f  operator*(sf::Vector2f& lhs, T val)
{
    return lhs *= val;
}