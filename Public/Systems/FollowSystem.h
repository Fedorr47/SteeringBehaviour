#pragma once
#include "BaseSystem.h"
#include "Utils/Utils.h"
#include "Components/Components.h"

void ManageFollow(VelocityComponent& velocity, ChaisingComponent& chaisingComp);

class FollowSystem : public BaseSystem {
public:
    virtual void update(entt::registry& registry, float deltaTime) override
    {
        auto view = registry.view<PositionComponent, VelocityComponent, ForceComponent, ChaisingComponent>();
        for (auto entity : view) {
            auto& position = view.get<PositionComponent>(entity);
            ChaisingComponent& chaising = registry.get<ChaisingComponent>(entity);
            auto& target_position = registry.get<PositionComponent>(chaising.object);

            VelocityComponent& velocity = view.get<VelocityComponent>(entity);
            auto& force = view.get<ForceComponent>(entity);            

            float distance = getLength(target_position.position - position.position);
            if (distance > 5.0f) {
                auto desired_velocity = normalize(target_position.position - position.position) * velocity.MaxSpeed;
                auto steering = truncate(desired_velocity - velocity.velocity, force.MaxForce);
                velocity.velocity += steering;
                ManageFollow(velocity, chaising);
            }
        }
    }
};

