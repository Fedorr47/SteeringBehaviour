#include "Systems/ObstaclesSystem.h"

#include "Components/Components.h"

// TODO: Rethink - maybe it would be better to use sectors logic - when map becomes larger
void ObstaclesSystem::update(float deltaTime)
{
    auto view = registry.view<ObstacleComponent, PositionComponent>();
    for (auto entity : view) {
        PositionComponent& position = view.get<PositionComponent>(entity);
        ObstacleComponent& obstacle = view.get<ObstacleComponent>(entity);
        
        obstacle.center = position.position;
        int id = static_cast<int>(entity);
        allObstacles[id] = &obstacle;
    };
}

