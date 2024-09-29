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

struct ChasingComponent
{
    MoveBehaviourType type = MoveBehaviourType::Seek;
    entt::entity object;
    float slowingRadius{ 0 };
    int velocity_multiplier{1}; 
};