#pragma once
#include "BaseSystem.h"
#include "Utils/Utils.h"
#include "Components/Components.h"

class BehaviourSystem : public BaseSystem {
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
            auto steering = truncate(desired_velocity - velocity.val, force.MaxForce);
            velocity.val = truncate(velocity.val + (steering / mass.mass), velocity.MaxSpeed);
            
            /*
            //sf::Vector2i mousePos = inputHandler.getMousePosition(window);
            sf::Vector2f target(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

            float stopThreshold = 5.0f; 
            float distanceToTarget = std::sqrt(std::pow(target.x - position.x, 2) +
                std::pow(target.y - position.y, 2));

            if (distanceToTarget > stopThreshold) {
                SeekMove(
                    position,
                    target,
                    velocity.val,
                    mass, 
                    Force.MaxForce,
                    velocity.MaxSpeed,
                    deltaTime);
            }
            else {
                velocity.val = { 0.0f, 0.0f };
            }
            */
        }
    }
};

