#pragma once
#include "BaseSystem.h"
#include "Utils/Utils.h"
#include "Utils/DebugInfo.h"
#include "Components/Components.h"

#include "ThirdParty/imgui/imgui-SFML.h"
#include "ThirdParty/imgui/imgui.h"
#include <random>

struct ManageParams
{
    int entity_id{ 0 };
    entt::registry* reg{ nullptr };
    VelocityComponent* velComp{nullptr};
    PositionComponent* posComp{ nullptr };
    ChasingComponent* chasComp{ nullptr };
    // debug info
    float distance{ 0 };
};

class FollowSystem : public BaseSystem {
public:
    virtual void update(entt::registry& registry, float deltaTime) override
    {
        auto view = registry.view<PositionComponent, VelocityComponent, ChasingComponent>();
        for (auto entity : view) {
            auto& position = view.get<PositionComponent>(entity);
            ChasingComponent& chaising = registry.get<ChasingComponent>(entity);
            VelocityComponent& velocity = view.get<VelocityComponent>(entity);          

            ManageParams params(
                static_cast<int>(entity),
                &registry,
                &velocity,
                &position,
                &chaising
            );
            ManageFollow(params);
        };
    }

    void ManageFollow(ManageParams& params);
    void GetVelocity(ManageParams& params);
    void Wander(ManageParams& params);
    void Seek(ManageParams& params);
    void Flee(ManageParams& params);

private:
    std::random_device dev;
};

