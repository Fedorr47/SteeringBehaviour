#pragma once

#include "BaseSystem.h"

struct ObstacleComponent;
struct VelocityComponent;
struct PositionComponent;
struct AvoidanceComponent;

struct ManageAvoidanceParams
{
    int entityID{ 0 };
    VelocityComponent* velComp{ nullptr };
    PositionComponent* posComp{ nullptr };
    AvoidanceComponent* avoidComp{ nullptr };
};

class AvoidanceSystem : public BaseSystem
{
public:
    AvoidanceSystem(entt::registry& registry) :
        BaseSystem(registry)
    {}

    virtual void update(float deltaTime) override;
    bool lineIntersectsCircle(sf::Vector2f& ahead, sf::Vector2f& ahead2, const ObstacleComponent& obstacle);
    sf::Vector2f CollosionAvoidance(ManageAvoidanceParams& params);
};