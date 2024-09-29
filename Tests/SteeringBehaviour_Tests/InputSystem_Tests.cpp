#include "pch.h"
/*
#include "Systems/InputSystem.h"
#include "EntityManager/EntityManager.h"
#include "Components/Components.h"
#include "MockInputHandler.h"

TEST(InputSystemTest, UpdateKeyboardInputTest) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
    MockInputHandler mockInputHandler;
    InputSystem inputSystem(500.0f, 200.0f, window, mockInputHandler);
    entt::registry registry;

    auto entity = registry.create();
    registry.emplace<VelocityComponent>(entity, sf::Vector2f(0.0f, 0.0f), 200.0f);
    registry.emplace<ControlComponent>(entity, false);

    mockInputHandler.setKeyPressed(sf::Keyboard::Left, true);

    inputSystem.update(registry, 1.0f);

    auto& velocity = registry.get<VelocityComponent>(entity);
    EXPECT_FLOAT_EQ(velocity.velocity.x, -velocity.speed);
}

TEST(InputSystemTest, UpdateMouseInputTest) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
    MockInputHandler mockInputHandler;
    InputSystem inputSystem(500.0f, 200.0f, window, mockInputHandler);
    entt::registry registry;

    auto entity = registry.create();
    registry.emplace<VelocityComponent>(entity, sf::Vector2f(0.0f, 0.0f), 200.0f);
    registry.emplace<ControlComponent>(entity, true);

    mockInputHandler.setMousePosition(sf::Vector2i(100, 100));

    inputSystem.update(registry, 1.0f);

    auto& velocity = registry.get<VelocityComponent>(entity);
    EXPECT_GT(velocity.velocity.x, 0.0f);
    EXPECT_GT(velocity.velocity.y, 0.0f);
}
*/