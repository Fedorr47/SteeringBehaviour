#include "Systems/AvoidanceSystem.h"

#include "Utils/Utils.h"
#include "Components/Components.h"

constexpr float MAX_AVOID_FORCE = 10.0f;

void AvoidanceSystem::update(float deltaTime)
{
    auto view = registry.view<PositionComponent, VelocityComponent, AvoidanceComponent>();
    for (auto entity : view) {
        PositionComponent& position = view.get<PositionComponent>(entity);
        VelocityComponent& velocity = view.get<VelocityComponent>(entity);
        AvoidanceComponent& avoidance = view.get<AvoidanceComponent>(entity);

        ManageAvoidanceParams params
        {
            static_cast<int>(entity),
            &velocity,
            &position,
            &avoidance
        };
    };
}


bool AvoidanceSystem::lineIntersectsCircle(sf::Vector2f& ahead, sf::Vector2f& ahead2, const ObstacleComponent& obstacle)
{
    return distance(obstacle.center, ahead) <= obstacle.radius || distance(obstacle.center, ahead2) <= obstacle.radius;
}

sf::Vector2f AvoidanceSystem::CollosionAvoidance(ManageAvoidanceParams& params)
{
    auto position = params.posComp->position;
    auto velocity = params.velComp->velocity;

    auto dynamic_length = getLength(velocity) / params.velComp->maxSpeed;
    auto ahead = position + normalize(velocity) * dynamic_length;
    auto ahead2 = ahead * 0.5f;

    ObstacleComponent* mostThreatening = params.avoidComp->Obstacles.top();

    sf::Vector2f avoidance;
    if (mostThreatening != nullptr) {
        avoidance.x = ahead.x - mostThreatening->center.x;
        avoidance.y = ahead.y - mostThreatening->center.y;
        avoidance = normalize(avoidance);
        avoidance *= MAX_AVOID_FORCE;
    }
    else {
        avoidance *= 0;
    }

    return avoidance;
}