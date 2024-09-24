#pragma once
#include <entt/entt.hpp>
#include "Systems/MovementSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/InputSystem.h"
#include "Components/Components.h"
#include "Settings/GameSettings.h"
#include "Systems/InputHandler.h"

class EntityManager
{
public:
    EntityManager(
        const GameSettings& settings, const InputHandler& inputHandler) :
        movementSystem(settings.window.getSize()),
        inputSystem(settings.maxForce, settings.maxSpeed, settings.window, inputHandler)
    {}

    entt::entity createPlayer(bool useMouseControl = false);
    entt::entity createNonPlayer();

    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    void SetFocusState(bool CurrentState);

    entt::registry& getRegistry() { return registry; }

private:
    entt::registry registry;

    //TODO: Add a generic class for all systems and create here vector of them
    MovementSystem movementSystem;
    RenderSystem renderSystem;
    InputSystem inputSystem;
};
