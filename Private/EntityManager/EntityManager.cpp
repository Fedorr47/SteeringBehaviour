#include "EntityManager/EntityManager.h"

EntityManager::EntityManager()
{
}

entt::entity EntityManager::createPlayer()
{
    auto player = registry.create();

    registry.emplace<PositionComponent>(player, sf::Vector2f(375.0f, 275.0f));
    registry.emplace<VelocityComponent>(player, sf::Vector2f(0.0f, 0.0f), 200.0f);

    sf::RectangleShape shape(sf::Vector2f(50.0f, 50.0f));
    shape.setFillColor(sf::Color::Green);
    registry.emplace<ShapeComponent>(player, shape);

    return player;
}

entt::entity EntityManager::createEnemy()
{
    auto enemy = registry.create();

    registry.emplace<PositionComponent>(enemy, sf::Vector2f(200.0f, 200.0f));
    registry.emplace<VelocityComponent>(enemy, sf::Vector2f(0.0f, 0.0f), 100.0f);

    sf::RectangleShape shape(sf::Vector2f(40.0f, 40.0f));
    shape.setFillColor(sf::Color::Red);
    registry.emplace<ShapeComponent>(enemy, shape);

    return enemy;
}

void EntityManager::update(float deltaTime)
{
    inputSystem.update(registry, deltaTime);
    movementSystem.update(registry, deltaTime);
}

void EntityManager::render(sf::RenderWindow& window)
{
    renderSystem.render(registry, window);
}
