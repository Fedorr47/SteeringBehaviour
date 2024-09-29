#pragma once
#include "BaseSystem.h"
#include "Utils/Utils.h"
#include "Components/Components.h"

class MovementSystem : public BaseSystem
{
private:
    sf::Vector2u windowSize;
public:
    MovementSystem(const sf::Vector2u& windowSize) : windowSize(windowSize) {}

    virtual void update(entt::registry& registry, float deltaTime) override
    {
        // TODO: add real size of an object aginst 50
        auto view = registry.view<PositionComponent, VelocityComponent, MassComponent>();
        for (auto entity : view) {
            auto& position = view.get<PositionComponent>(entity);
            auto& velocity = view.get<VelocityComponent>(entity);
            auto& mass = view.get<MassComponent>(entity);
            
            position.position += truncate(velocity.velocity + (velocity.velocity / mass.mass), velocity.MaxSpeed) * deltaTime;

            if (position.position.x < 0) {
                position.position.x = 0;
            }
            else if (position.position.x + 50 > windowSize.x) {
                position.position.x = windowSize.x - 50;
            }

            if (position.position.y < 0) {
                position.position.y = 0;
            }
            else if (position.position.y + 50 > windowSize.y) {
                position.position.y = windowSize.y - 50;
            }
            
        }
    }
};
