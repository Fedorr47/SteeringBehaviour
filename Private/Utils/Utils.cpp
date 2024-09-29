#include "Utils/Utils.h"

#include <cmath>

float getLength(const sf::Vector2f& vec)
{
    return std::sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

sf::Vector2f truncate(const sf::Vector2f& vec, float max) {
    float length = getLength(vec);
    if (length > max) {
        return vec * (max / length);
    }
    return vec;
}

sf::Vector2f normalize(const sf::Vector2f& source)
{
    float length = getLength(source);
    if (length != 0)
        return sf::Vector2f(source.x / length, source.y / length);
    else
        return source;
}