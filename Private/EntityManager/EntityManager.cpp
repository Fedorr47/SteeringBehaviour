#include <memory>
#include "EntityManager/EntityManager.h"
#include "Systems/MovementSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/BehaviourSystem.h"

EntityManager::EntityManager(const GameSettings& settings, const InputHandler& inputHandler)
{
    Systems.emplace("MovementSystem", std::unique_ptr<MovementSystem>(new MovementSystem(settings.window.getSize())));
    Systems.emplace("InputSystem", std::unique_ptr<InputSystem>(new InputSystem(settings.maxForce, settings.maxSpeed, settings.window, inputHandler)));
    Systems.emplace("BehaviourSystem", std::make_unique<BehaviourSystem>());
    RenderSys = std::make_unique<RenderSystem>();
}

entt::entity EntityManager::createPlayer(bool useMouseControl /*= false*/)
{
    auto player = registry.create();

    registry.emplace<PositionComponent>(player, sf::Vector2f(375.0f, 275.0f));
    registry.emplace<VelocityComponent>(player, sf::Vector2f(0.0f, 0.0f), 200.0f, 200.0f);
    registry.emplace<MassComponent>(player, 100.0f);

    sf::RectangleShape shape(sf::Vector2f(50.0f, 50.0f));
    shape.setFillColor(sf::Color::Green);
    registry.emplace<ShapeComponent>(player, shape);

    
    registry.emplace<ForceComponent>(player, 200.0f, 500.0f);

    //DEBUG
    registry.emplace<ControlComponent>(player, useMouseControl, true); // TODO - transfrom to follow component
    registry.emplace<FollowComponent>(player, sf::Vector2f(0.0f,0.0f));
    registry.emplace<BehaviourComponent>(player);
    // END DEBUG

    return player;
}

entt::entity EntityManager::createNonPlayer()
{
    auto enemy = registry.create();

    registry.emplace<PositionComponent>(enemy, sf::Vector2f(200.0f, 200.0f));
    registry.emplace<VelocityComponent>(enemy, sf::Vector2f(0.0f, 0.0f), 100.0f, 100.0f);
    registry.emplace<MassComponent>(enemy, 2.0f);

    sf::RectangleShape shape(sf::Vector2f(40.0f, 40.0f));
    shape.setFillColor(sf::Color::Red);
    registry.emplace<ShapeComponent>(enemy, shape);

    return enemy;
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
