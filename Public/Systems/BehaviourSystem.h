#pragma once
#include "BaseSystem.h"
#include "Utils/Utils.h"
#include "Components/Components.h"

class FollowSystem : public BaseSystem {
public:
    virtual void update(entt::registry& registry, float deltaTime) override
    {
        auto view = registry.view<
            FollowComponent, 
            VelocityComponent, 
            PositionComponent,
            ForceComponent,
            MassComponent>();
        for (auto entity : view) 
        {
            auto& follow = view.get<FollowComponent>(entity);
            auto& position = view.get<PositionComponent>(entity).position;
            auto& velocity = view.get<VelocityComponent>(entity);
            auto& force = view.get<ForceComponent>(entity);
            auto& mass = view.get<MassComponent>(entity);

            auto desired_velocity = normalize(follow.endPos - position) * velocity.MaxSpeed;

            if (follow.type == MoveBehaviourType::Flee)
            {
                desired_velocity = -desired_velocity;
            }

            auto steering = truncate(desired_velocity - velocity.val, force.MaxForce);
            velocity.val = truncate(velocity.val + (steering / mass.mass), velocity.MaxSpeed);
        }
    }
};

