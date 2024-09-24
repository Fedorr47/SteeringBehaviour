#pragma once
#include <entt/entt.hpp>
#include "Components/Components.h"

class PositionSystem {
public:
    void update(entt::registry& registry, float deltaTime) {
        auto view = registry.view<PositionComponent, VelocityComponent>();
        for (auto entity : view) {
            auto& position = view.get<PositionComponent>(entity);
            auto& velocity = view.get<VelocityComponent>(entity);

            position.position += velocity.velocity * deltaTime;
        }
    }
};