#include <memory>
#include "Utils/DebugInfo.h"
#include "EntityManager/EntityManager.h"
#include "Systems/MovementSystem.h"
#include "Systems/PathSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/FollowSystem.h"
#include "Systems/ShapeSystem.h"
#include "Systems/ObstaclesSystem.h"
#include "Systems/AvoidanceSystem.h"

std::unordered_map<int, ObstacleComponent*> allObstacles;

EntityManager::EntityManager(const GameSettings& settings, const InputHandler& inputHandler, std::shared_ptr<DebugInfo> debugInfo)
{
    Systems.push_back({ "MovementSystem", std::make_unique<MovementSystem>(registry, settings.window.getSize()) });
    Systems.push_back({ "InputSystem", std::make_unique<InputSystem>(registry, settings.maxForce, settings.maxSpeed, settings.window, inputHandler) });
    Systems.push_back({ "FollowSystem", std::make_unique<FollowSystem>(registry) });
    Systems.push_back({ "ObstaclesSystem", std::make_unique<ObstaclesSystem>(registry) });
    Systems.push_back({ "AvoidanceSystem", std::make_unique<AvoidanceSystem>(registry) });
    Systems.push_back({ "PathSystem", std::make_unique<PathSystem>(registry) });
    Systems.push_back({ "ShapeSystem", std::make_unique<ShapeSystem>(registry) });

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
