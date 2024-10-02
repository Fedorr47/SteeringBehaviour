#include "Utils/Utils.h"

#include <cmath>

constexpr float Degree180 = 180.0f;

float getLength(const sf::Vector2f& vec)
{
    return std::sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

sf::Vector2f truncate(const sf::Vector2f& vec, float max) 
{
    sf::Vector2f ret_vec = vec;
    float length = getLength(vec);
    float i = max / length;
    i = i < 1.0f ? i : 1.0f;
    ret_vec *= i;
    return ret_vec;
}

sf::Vector2f normalize(const sf::Vector2f& source)
{
    float length = getLength(source);
    if (length != 0)
        return sf::Vector2f(source.x / length, source.y / length);
    else
        return source;
}

float toRadians(float angle)
{
    return static_cast<float>(angle * std::numbers::pi / Degree180);
}

float toDegrees(float radians)
{
    return static_cast<float>(radians * Degree180 / std::numbers::pi);
}

void setAngle(sf::Vector2f& vector, float angle)
{
    float radians = toRadians(angle);
    float length = getLength(vector);
    vector.x = std::cos(radians) * length;
    vector.y = std::sin(radians) * length;
}

float computeTargetAngle(const sf::Vector2f& vector)
{

    return std::atan2(vector.y, vector.x) * Degree180 / std::numbers::pi;
}
