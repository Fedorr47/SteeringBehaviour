#pragma once
#include <SFML/Graphics.hpp>

struct PositionComponent
{
    sf::Vector2f position;
};

struct VelocityComponent
{
    sf::Vector2f velocity;
    float speed;
};

struct ShapeComponent
{
    sf::RectangleShape shape;
};