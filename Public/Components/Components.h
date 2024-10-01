#pragma once
#include <SFML/Graphics.hpp>
#include <variant>

#include "MovementBehaviour.h"

struct PositionComponent
{
    sf::Vector2f position;
    float angle{ 0.0f };
};

struct VelocityComponent
{
    sf::Vector2f velocity;
    float speed;
    float MaxSpeed;
};

struct ShapeComponent
{
    sf::ConvexShape shape;
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
    Wander,
    NONE
};

struct SeekFleeBehavior : public MovementBehaviour
{
    SeekFleeBehavior(
        entt::entity object,
        float slowingRadius) :
        MovementBehaviour(object, slowingRadius)
    {}
};

struct ChasingComponent
{
    MoveBehaviourType type = MoveBehaviourType::Seek;   
    MovementBehaviour* Behavior{nullptr};
};


/*
template <MoveBehaviourType T, typename = void>
struct ChasingComponent;

template <MoveBehaviourType T>
struct ChasingComponent<T, typename std::enable_if_t<T != MoveBehaviourType::Wander>> {
    entt::entity object;
    float slowingRadius{ 0 };
};

template <MoveBehaviourType T>
struct ChasingComponent<T, typename std::enable_if_t<T == MoveBehaviourType::Wander>> {
    sf::Vector2f targetPosition;
    float nextDecisionTime{ 0.0f };
};
*/