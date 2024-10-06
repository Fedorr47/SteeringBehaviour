#include <memory>
#include "Utils/DebugInfo.h"
#include "EntityManager/EntityManager.h"
#include "Systems/MovementSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/FollowSystem.h"
#include "Systems/ShapeSystem.h"

EntityManager::EntityManager(const GameSettings& settings, const InputHandler& inputHandler, std::shared_ptr<DebugInfo> debugInfo)
{
    Systems.emplace("MovementSystem", std::unique_ptr<MovementSystem>(new MovementSystem(registry, settings.window.getSize())));
    Systems.emplace("InputSystem", std::unique_ptr<InputSystem>(new InputSystem(registry, settings.maxForce, settings.maxSpeed, settings.window, inputHandler)));
    Systems.emplace("FollowSystem", std::make_unique<FollowSystem>(registry));
    Systems.emplace("ShapeSystem", std::make_unique<ShapeSystem>(registry));

    RenderSys = std::make_unique<RenderSystem>(registry);
    for (auto& [_, system] : Systems)
    {
        system->debugInfo = debugInfo->getptr();
    }
}

entt::entity EntityManager::createEntity()
{
    auto entity = registry.create();
    return entity;
}

void EntityManager::update(float deltaTime)
{
    for (auto& [_, system] : Systems)
    {
        system->update(deltaTime);
    }
}

void EntityManager::render(sf::RenderWindow& window)
{
    RenderSys->render(window);
}

void EntityManager::SetFocusState(bool CurrentState)
{
    //inputSystem.SetFocusState(CurrentState);
}
