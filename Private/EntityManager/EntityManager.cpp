#include "EntityManager/EntityManager.h"

entt::entity EntityManager::createPlayer(bool useMouseControl /*= false*/)
{
    auto player = registry.create();

    registry.emplace<PositionComponent>(player, sf::Vector2f(375.0f, 275.0f));
    registry.emplace<VelocityComponent>(player, sf::Vector2f(0.0f, 0.0f), 200.0f);
    registry.emplace<MassComponent>(player, 100.0f);

    sf::RectangleShape shape(sf::Vector2f(50.0f, 50.0f));
    shape.setFillColor(sf::Color::Green);
    registry.emplace<ShapeComponent>(player, shape);

    registry.emplace<ControlComponent>(player, useMouseControl, true);

    return player;
}

entt::entity EntityManager::createNonPlayer()
{
    auto enemy = registry.create();

    registry.emplace<PositionComponent>(enemy, sf::Vector2f(200.0f, 200.0f));
    registry.emplace<VelocityComponent>(enemy, sf::Vector2f(0.0f, 0.0f), 100.0f);
    registry.emplace<MassComponent>(enemy, 2.0f);

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

void EntityManager::SetFocusState(bool CurrentState)
{
    inputSystem.SetFocusState(CurrentState);
}
