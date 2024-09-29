#pragma once
#include <SFML/System/Vector2.hpp>
#include <concepts>

float getLength(const sf::Vector2f& vec);
sf::Vector2f truncate(const sf::Vector2f& vec, float max); 
sf::Vector2f normalize(const sf::Vector2f& source);

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

