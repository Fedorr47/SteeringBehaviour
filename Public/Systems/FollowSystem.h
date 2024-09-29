#pragma once
#include "BaseSystem.h"
#include "Utils/Utils.h"
#include "Utils/DebugInfo.h"
#include "Components/Components.h"

#include "ThirdParty/imgui/imgui-SFML.h"
#include "ThirdParty/imgui/imgui.h"

void ManageFollow(VelocityComponent& velocity, ChasingComponent& chaisingComp);

class FollowSystem : public BaseSystem {
public:
    virtual void update(entt::registry& registry, float deltaTime) override
    {
        auto view = registry.view<PositionComponent, VelocityComponent, ForceComponent, ChasingComponent>();
        for (auto entity : view) {
            auto& position = view.get<PositionComponent>(entity);
            ChasingComponent& chaising = registry.get<ChasingComponent>(entity);
            auto& target_position = registry.get<PositionComponent>(chaising.object);

            VelocityComponent& velocity = view.get<VelocityComponent>(entity);
            auto& force = view.get<ForceComponent>(entity);            

            auto desired_velocity = target_position.position - position.position;
            float distance = getLength(desired_velocity);

            if (distance < chaising.slowingRadius) {
                desired_velocity = normalize(desired_velocity) * velocity.MaxSpeed * (distance / chaising.slowingRadius);
            }
            else {
                desired_velocity = normalize(desired_velocity) * velocity.MaxSpeed;
            }

            auto steering = desired_velocity - velocity.velocity;
            velocity.velocity += steering;

            ManageFollow(velocity, chaising);

            FollowDebugInfo info;
            info.entityID = static_cast<int>(entity);
            info.position = position.position;
            info.velocity = velocity.velocity;
            info.distanceToTarget = distance;
            debugInfo->chasingEntities[static_cast<int>(entity)] = info;
        };
    }
};

