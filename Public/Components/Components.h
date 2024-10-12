#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include <unordered_map>

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
    float maxSpeed;
    sf::Vector2f steering;
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

struct ChasingComponent
{
    std::vector<MovementBehavior*> Behaviors;
};

struct ObstacleComponent
{
    float radius{ 0.0f };
    sf::Vector2f center; 
};

struct AvoidanceComponent
{
    float radiusToSee{ 0.0f };
    ObstacleComponent* theNearstOne{ nullptr };
};

// Global data
extern std::unordered_map<int, ObstacleComponent*> allObstacles;

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