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

struct MassComponent {
    float mass;
};

struct ControlComponent {
    bool useMouseControl;
    bool autoSwitch;
};

struct FocusComponent
{
    bool isFocusLost = false;
};