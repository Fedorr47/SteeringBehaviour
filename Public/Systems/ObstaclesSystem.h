#pragma once

#include "BaseSystem.h"

struct ObstacleComponent;
struct PositionComponent;
struct AvoidanceComponent;

class ObstaclesSystem : public BaseSystem
{
public:
    ObstaclesSystem(entt::registry& registry) :
        BaseSystem(registry)
    {}

    virtual void update(float deltaTime) override;
};

/*
Obstacle CollisionSystem::findMostThreateningObstacle()
{
    Obstacle mostThreatening;
    for (var i : int = 0; i < Game.instance.obstacles.length; i++) {
        var obstacle : Obstacle = Game.instance.obstacles[i];
        var collision : Boolean = lineIntersecsCircle(ahead, ahead2, obstacle);
        // "position" is the character's current position 
        if (collision && (mostThreatening == null || distance(position, obstacle) < distance(position, mostThreatening))) {
            mostThreatening = obstacle;
        }
    }
    return mostThreatening;
}
*/