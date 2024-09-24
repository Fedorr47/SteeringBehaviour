#include "pch.h"
#include "Systems/InputSystem.h"
#include "EntityManager/EntityManager.h"
#include "Components/Components.h"

TEST(InputSystemTest, UpdateInputTest) {
    entt::registry registry;
    InputSystem inputSystem;

    auto entity = registry.create();
    registry.emplace<VelocityComponent>(entity, sf::Vector2f(0.0f, 0.0f), 100.0f);

    // Here you will need to emulate keypresses
    // For example, through mock functions or the SFML event system

    inputSystem.update(registry, 1.0f);
    auto& velocity = registry.get<VelocityComponent>(entity);

    EXPECT_EQ(velocity.velocity.x, 0.0f);
    EXPECT_EQ(velocity.velocity.y, 0.0f);
}