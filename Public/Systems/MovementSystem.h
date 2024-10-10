#pragma once
#include "BaseSystem.h"

class MovementSystem : public BaseSystem
{
private:
    sf::Vector2u windowSize;
public:
    MovementSystem(
        entt::registry& registry,
        const sf::Vector2u& windowSize) :
        BaseSystem(registry), 
        windowSize(windowSize) {}

    virtual void update(float deltaTime) override;
};
