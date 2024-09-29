#pragma once
#include "BaseSystem.h"
#include "Utils/Utils.h"
#include "Components/Components.h"

class FollowSystem : public BaseSystem {
public:
    virtual void update(entt::registry& registry, float deltaTime) override
    {
        auto view = registry.view<PositionComponent, VelocityComponent, ForceComponent, ChaisingComponent>();
        for (auto entity : view) {
            auto& position = view.get<PositionComponent>(entity);
            auto& chaising = registry.get<ChaisingComponent>(entity);
            auto& target_position = registry.get<PositionComponent>(chaising.object);

            auto& velocity = view.get<VelocityComponent>(entity);
            auto& force = view.get<ForceComponent>(entity);            

            auto desired_velocity = normalize(target_position.position - position.position) * velocity.MaxSpeed;
            velocity.velocity = truncate(desired_velocity - velocity.velocity, force.MaxForce);
        }
    }
};

