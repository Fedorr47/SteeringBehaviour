#include "pch.h"
#include "EntityManager/EntityManager.h"
#include "Components/Components.h"

TEST(EntityManagerTest, CreatePlayerTest) {
    EntityManager entityManager;
    auto player = entityManager.createPlayer();

    EXPECT_TRUE(entityManager.getRegistry().valid(player));

    EXPECT_TRUE(entityManager.getRegistry().all_of<PositionComponent>(player));
    EXPECT_TRUE(entityManager.getRegistry().all_of<VelocityComponent>(player));
    EXPECT_TRUE(entityManager.getRegistry().all_of<ShapeComponent>(player));
}

TEST(EntityManagerTest, CreateBotTest) {
    EntityManager entityManager;
    auto bot = entityManager.createEnemy();

    EXPECT_TRUE(entityManager.getRegistry().valid(bot));

    EXPECT_TRUE(entityManager.getRegistry().all_of<PositionComponent>(bot));
    EXPECT_TRUE(entityManager.getRegistry().all_of<VelocityComponent>(bot));
    EXPECT_TRUE(entityManager.getRegistry().all_of<ShapeComponent>(bot));
}
