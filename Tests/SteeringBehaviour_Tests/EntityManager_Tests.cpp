#include "pch.h"
#include "EntityManager/EntityManager.h"
#include "Components/Components.h"
#include "MockInputHandler.h"

TEST(EntityManagerTest, CreatePlayerTest) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
    GameSettings settings{ 500.0f, 200.0f, window };
    MockInputHandler mockInputHandler;
    EntityManager entityManager(settings, mockInputHandler);

    auto player = entityManager.createPlayer(false);

    EXPECT_TRUE(entityManager.getRegistry().valid(player));

    EXPECT_TRUE(entityManager.getRegistry().all_of<PositionComponent>(player));
    EXPECT_TRUE(entityManager.getRegistry().all_of<VelocityComponent>(player));
    EXPECT_TRUE(entityManager.getRegistry().all_of<MassComponent>(player));
    EXPECT_TRUE(entityManager.getRegistry().all_of<ControlComponent>(player));
}

TEST(EntityManagerTest, CreateNonPlayer) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
    GameSettings settings{ 500.0f, 200.0f, window };
    MockInputHandler mockInputHandler;
    EntityManager entityManager(settings, mockInputHandler);

    auto enemy = entityManager.createNonPlayer();

    EXPECT_TRUE(entityManager.getRegistry().valid(enemy));

    EXPECT_TRUE(entityManager.getRegistry().all_of<PositionComponent>(enemy));
    EXPECT_TRUE(entityManager.getRegistry().all_of<VelocityComponent>(enemy));
    EXPECT_TRUE(entityManager.getRegistry().all_of<MassComponent>(enemy));
}
