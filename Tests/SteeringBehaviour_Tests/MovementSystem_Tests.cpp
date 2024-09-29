#include "pch.h"
//#include "Systems/MovementSystem.h"
//#include "EntityManager/EntityManager.h"
//#include "Components/Components.h"
/*
TEST(MovementSystemTest, UpdateMovementTest) {
    entt::registry registry;
    sf::Vector2u windowSize(800, 600);
    MovementSystem movementSystem(windowSize);

    auto entity = registry.create();
    registry.emplace<PositionComponent>(entity, sf::Vector2f(0.0f, 0.0f));
    registry.emplace<VelocityComponent>(entity, sf::Vector2f(1.0f, 1.0f), 100.0f);
    registry.emplace<MassComponent>(entity, 1.0f);

    movementSystem.update(registry, 1.0f);

    auto& position = registry.get<PositionComponent>(entity);
    EXPECT_FLOAT_EQ(position.position.x, 100.0f);
    EXPECT_FLOAT_EQ(position.position.y, 100.0f);
}
*/
