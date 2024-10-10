#pragma once

#include "BaseSystem.h"

class CollisionSystem : public BaseSystem
{
public:
    CollisionSystem(entt::registry& registry) :
        BaseSystem(registry)
    {}

    virtual void update(float deltaTime) override;
    bool lineIntersectsCircle(sf::Vector2f& ahead, sf::Vector2f& ahead2, const sf::Vector2f& center, float radius);
    sf::Vector2f CollosionAvoidance();
};