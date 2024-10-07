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
    int entityID{ 0 };
    entt::registry* reg{ nullptr };
    VelocityComponent* velComp{nullptr};
    PositionComponent* posComp{ nullptr };
    ChasingComponent* chasComp{ nullptr };
    float deltaTime{ 0.0f };
    MovementBehavior* currentBehavior{ nullptr };
    sf::Vector2f targetPos;
    // debug info
    FollowDebugInfo info;
};

class FollowSystem : public BaseSystem {
public:

    FollowSystem(entt::registry& registry) :
        BaseSystem(registry)
    {}

    virtual void update(float deltaTime) override
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
                &chaising,
                deltaTime
            );
            ManageFollow(params);
        };
    }

    void ManageFollow(ManageParams& params);
    void PredictPostion(ManageParams& params);
    sf::Vector2f Wander(ManageParams& params);
    sf::Vector2f Pursuit(ManageParams& params);
    sf::Vector2f Evade(ManageParams& params);
    template <typename Compare>
    sf::Vector2f SeekOrFlee(ManageParams& params, Compare comp, bool inverse = false);
    sf::Vector2f Seek(ManageParams& params);
    sf::Vector2f Flee(ManageParams& params);

private:
    std::random_device dev;
};

