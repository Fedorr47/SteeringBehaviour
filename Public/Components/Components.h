#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include <unordered_map>

#include "MovementBehaviour.h"
#include "Flock.h"

struct PositionComponent
{
    sf::Vector2f position;
    float angle{ 0.0f };
    bool isCorrecting{ false };
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
    bool isFocusLost{ false };
};

struct ChasingComponent
{
    std::vector<std::shared_ptr<MovementBehavior>> Behaviors;
};

struct ObstacleComponent
{
    float radius{ 0.0f };
    sf::Vector2f center; 
};

struct AvoidanceComponent
{
    float radiusToSee{ 0.0f };
    float maxAvoidForce{ 0.0f };
    std::shared_ptr<ObstacleComponent> theNearstOne{ nullptr };
};

struct PathComponent {
    PathComponent(std::initializer_list<sf::Vector2f> initList) {
        for (auto vec : initList)
        {
            nodes.push_back({entt::null, vec});
        }
    }
    std::vector<NodeOfPath> nodes;
    float distanceToChangeNode{ 0.0f };
    int currentNode{ -1 };
    std::shared_ptr<MovementBehavior> pathBehavior{nullptr};
};

struct FlockComponent
{
    std::shared_ptr<FlockActor> actor;
    float leaderBehindDist{ 0.0f };
    float leaderSightRadius{ 0.0f };
    float separationRadius{ 0.0f };
    float maxSeparation{ 0.0f };
};

// Global data
extern std::unordered_map<int, std::shared_ptr<ObstacleComponent>> allObstacles;

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