#pragma once
#include <SFML/Graphics.hpp>

struct PositionComponent
{
    sf::Vector2f position;
};

struct VelocityComponent
{
    sf::Vector2f val;
    float speed;
    float MaxSpeed;
};

struct ForceComponent
{
    float Force;
    float MaxForce;
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

enum class MoveBehaviourType : char
{
    Seek,
    Flee,
    NONE
};

struct BehaviourComponent
{
    MoveBehaviourType type = MoveBehaviourType::Seek;
};

struct FollowComponent
{
    sf::Vector2f endPos;
};

struct PathComponent
{
    sf::Vector2f startPoint;
    sf::Vector2f endPoint;
};