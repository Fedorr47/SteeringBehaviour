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

sf::Vector2f setAngle(sf::Vector2f& vector, float angle)
{
    float radians = toRadians(angle);
    float cosTheta = cos(radians);
    float sinTheta = sin(radians);
    return {
        vector.x * cosTheta - vector.y * sinTheta,
        vector.x * sinTheta + vector.y * cosTheta
    };
}

float computeTargetAngle(const sf::Vector2f& vector)
{

    return std::atan2(vector.y, vector.x) * Degree180 / std::numbers::pi;
}

float distance(const sf::Vector2f& obj1, const sf::Vector2f& obj2)
{
    return sqrt((obj1.x - obj2.x) * (obj1.x - obj2.x) + (obj1.y - obj2.y) * (obj1.y - obj2.y));
}

float randomFloat(float min, float max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}