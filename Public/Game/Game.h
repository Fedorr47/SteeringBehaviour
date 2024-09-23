#pragma once
#include "Player/Player.h"
#include "Window/Window.h"
#include "Components/Components.h"
#include "Systems/MovementSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/InputSystem.h"

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();

    Window window;  // Окно игры
    entt::registry registry;

    // Системы игры
    MovementSystem movementSystem;
    RenderSystem renderSystem;
    InputSystem inputSystem;

    sf::Clock clock;
    void createPlayer();
};