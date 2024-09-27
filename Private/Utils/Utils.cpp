#include "Utils/Utils.h"

#include <cmath>

sf::Vector2f truncate(const sf::Vector2f& vec, float max) {
    float length = std::sqrt(vec.x * vec.x + vec.y * vec.y);
    if (length > max) {
        return vec * (max / length);
    }
    return vec;
}

sf::Vector2f normalize(const sf::Vector2f& source)
{
    float length = std::sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return sf::Vector2f(source.x / length, source.y / length);
    else
        return source;
}