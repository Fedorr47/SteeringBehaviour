#pragma once
#include "BaseSystem.h"
#include "Utils/Utils.h"
#include "Components/Components.h"

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

    virtual void update(float deltaTime) override
    {
        // TODO: add real size of an object aginst 50
        auto view = registry.view<PositionComponent, VelocityComponent, MassComponent>();
        for (auto entity : view) {
            auto& position = view.get<PositionComponent>(entity);
            auto& velocity = view.get<VelocityComponent>(entity);
            auto& mass = view.get<MassComponent>(entity);

            if (getLength(velocity.steering) > 0.00000001)
            {
                velocity.velocity = truncate(velocity.velocity + truncate(velocity.steering, 100.0f) / mass.mass, velocity.maxSpeed);
                position.position = position.position + velocity.velocity * deltaTime;
            }
            else
            {
                position.position += truncate(velocity.velocity + (velocity.velocity / mass.mass), velocity.maxSpeed) * deltaTime;
            }
            position.angle = computeTargetAngle(velocity.velocity) + 90.0f;

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
