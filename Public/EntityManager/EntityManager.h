#pragma once
#include <entt/entt.hpp>
#include "Systems/MovementSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/InputSystem.h"
#include "Components/Components.h"

class EntityManager
{
public:
    EntityManager();

    entt::entity createPlayer();
    entt::entity createEnemy();

    void update(float deltaTime);

    void render(sf::RenderWindow& window);

private:
    entt::registry registry;

    // Системы
    MovementSystem movementSystem;
    RenderSystem renderSystem;
    InputSystem inputSystem;
};
