#include "pch.h"
#include <memory>
#include "EntityManager/EntityManager.h"
#include "Components/Components.h"
#include "MockInputHandler.h"

class EntityManagerTest : public ::testing::Test {
protected:
    std::unique_ptr<GameSettings> settings;
    std::unique_ptr<EntityManager> entityManager;
    std::unique_ptr<MockInputHandler> inputHandler;
    std::unique_ptr<sf::RenderWindow> window;

    void SetUp() override {
        window = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(800, 600), "Test"));
        settings = std::unique_ptr<GameSettings>(new GameSettings(500.0f, 200.0f, *window, true, 60));
        inputHandler = std::make_unique<MockInputHandler>();
        entityManager = std::unique_ptr<EntityManager>(new EntityManager(*settings.get(), *inputHandler.get()));
    }

    void TearDown() override {
    }
};

// Тестируем создание игрока
TEST_F(EntityManagerTest, CreatePlayerTest) {
    auto player = entityManager->createPlayer(true);
    auto& registry = entityManager->getRegistry();

    EXPECT_TRUE(registry.valid(player));

    EXPECT_TRUE(registry.all_of<PositionComponent>(player));
    EXPECT_TRUE(registry.all_of<VelocityComponent>(player));
    EXPECT_TRUE(registry.all_of<MassComponent>(player));
}

// Тестируем создание врага
TEST_F(EntityManagerTest, CreateEnemyTest) {
    auto enemy = entityManager->createNonPlayer();
    auto& registry = entityManager->getRegistry();

    EXPECT_TRUE(registry.valid(enemy));

    EXPECT_TRUE(registry.all_of<PositionComponent>(enemy));
    EXPECT_TRUE(registry.all_of<VelocityComponent>(enemy));
    EXPECT_TRUE(registry.all_of<ShapeComponent>(enemy));
}

TEST_F(EntityManagerTest, UpdateSystemTest) {
    auto player = entityManager->createPlayer(true);

    entityManager->update(0.016f);

    auto& registry = entityManager->getRegistry();
    auto& pos = registry.get<PositionComponent>(player);

    EXPECT_NE(pos.position, sf::Vector2f(0, 0));
}

TEST_F(EntityManagerTest, DeleteEntityTest) {
    auto player = entityManager->createPlayer(true);
    auto& registry = entityManager->getRegistry();

    EXPECT_TRUE(registry.valid(player));

    registry.destroy(player);

    EXPECT_FALSE(registry.valid(player));
}