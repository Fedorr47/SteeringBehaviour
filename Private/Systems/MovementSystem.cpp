﻿#include "Systems/MovementSystem.h"
#include "Utils/Utils.h"
#include "Components/Components.h"

void MovementSystem::update(float deltaTime)
{
    // TODO: add real size of an object aginst 50
    auto view = registry.view<PositionComponent, VelocityComponent, MassComponent>();
    for (auto entity : view) {
        auto& position = view.get<PositionComponent>(entity);
        auto& velocity = view.get<VelocityComponent>(entity);
        auto& mass = view.get<MassComponent>(entity);

        if (velocity.ruledBySteering)
        {
            velocity.velocity = truncate(velocity.velocity + truncate(velocity.steering, 100.0f) / mass.mass, velocity.maxSpeed);
            position.position = position.position + velocity.velocity * deltaTime;
            velocity.steering = sf::Vector2f(0.0f, 0.0f);
        }
        else
        {
            velocity.velocity = truncate(velocity.velocity + (velocity.velocity / mass.mass), velocity.maxSpeed);
            position.position = position.position + velocity.velocity * deltaTime;
        }

        if (getLength(velocity.velocity) > velocity.stopThreshold) {
            position.angle = computeTargetAngle(velocity.velocity) + 90.0f;
            position.lastAngle = position.angle;
        }
        else {
            position.angle = position.lastAngle;
        }

        if (position.position.x < 0) 
        {
            position.position.x = 0;
        }
        else if (position.position.x + 50 > windowSize.x) 
        {
            position.position.x = windowSize.x - 50;
        }

        if (position.position.y < 0) {
            position.position.y = 0;
        }
        else if (position.position.y + 50 > windowSize.y) 
        {
            position.position.y = windowSize.y - 50;
        }
    }
}
