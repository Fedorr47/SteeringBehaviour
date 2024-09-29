#include <memory>
#include "EntityManager/EntityManager.h"
#include "Systems/MovementSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/FollowSystem.h"

EntityManager::EntityManager(const GameSettings& settings, const InputHandler& inputHandler)
{
    Systems.emplace("MovementSystem", std::unique_ptr<MovementSystem>(new MovementSystem(settings.window.getSize())));
    Systems.emplace("InputSystem", std::unique_ptr<InputSystem>(new InputSystem(settings.maxForce, settings.maxSpeed, settings.window, inputHandler)));
    Systems.emplace("FollowSystem", std::make_unique<FollowSystem>());
    RenderSys = std::make_unique<RenderSystem>();
}

entt::entity EntityManager::createPlayer(bool useMouseControl /*= false*/)
{
    auto player = registry.create();

    registry.emplace<PositionComponent>(player, sf::Vector2f(375.0f, 275.0f));
    registry.emplace<VelocityComponent>(player, sf::Vector2f(0.0f, 0.0f), 200.0f, 200.0f);
    registry.emplace<MassComponent>(player, 100.0f);

    sf::RectangleShape shape(sf::Vector2f(10.0f, 10.0f));
    shape.setFillColor(sf::Color::Green);
    registry.emplace<ShapeComponent>(player, shape);
    registry.emplace<ForceComponent>(player, 200.0f, 500.0f);
    registry.emplace<ControlComponent>(player, useMouseControl, false);

    return player;
}

entt::entity EntityManager::createNonPlayer()
{
    auto nonPlayerEntity = registry.create();

    registry.emplace<PositionComponent>(nonPlayerEntity, sf::Vector2f(200.0f, 200.0f));
    registry.emplace<VelocityComponent>(nonPlayerEntity, sf::Vector2f(0.0f, 0.0f), 100.0f, 100.0f);
    registry.emplace<MassComponent>(nonPlayerEntity, 150.0f);

    sf::RectangleShape shape(sf::Vector2f(40.0f, 40.0f));
    shape.setFillColor(sf::Color::Red);
    registry.emplace<ShapeComponent>(nonPlayerEntity, shape);
    registry.emplace<ForceComponent>(nonPlayerEntity, 200.0f, 500.0f);

    return nonPlayerEntity;
}

void EntityManager::update(float deltaTime)
{
    for (auto& [_, system] : Systems)
    {
        system->update(registry, deltaTime);
    }
}

void EntityManager::render(sf::RenderWindow& window)
{
    RenderSys->render(registry, window);
}

void EntityManager::SetFocusState(bool CurrentState)
{
    //inputSystem.SetFocusState(CurrentState);
}
