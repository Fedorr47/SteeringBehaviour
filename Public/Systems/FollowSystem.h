#pragma once
#include "BaseSystem.h"
#include "Utils/DebugInfo.h"
#include <random>

struct VelocityComponent;
struct PositionComponent;
struct ChasingComponent;
struct MovementBehavior;

struct ManageFollowParams
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

    virtual void update(float deltaTime) override;
    virtual void init() override;

    void ManageFollow(ManageFollowParams& params);
    void PredictPostion(ManageFollowParams& params);
    sf::Vector2f Wander(ManageFollowParams& params);
    sf::Vector2f Pursuit(ManageFollowParams& params);
    sf::Vector2f Evade(ManageFollowParams& params);
    template <typename Compare>
    sf::Vector2f SeekOrFlee(ManageFollowParams& params, Compare comp, bool inverse = false);
    sf::Vector2f Seek(ManageFollowParams& params);
    sf::Vector2f Flee(ManageFollowParams& params);

private:
    std::random_device dev;
};

