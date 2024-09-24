#pragma once
#include "Window/Window.h"
#include "EntityManager/EntityManager.h"
#include "Settings/GameSettings.h"
#include <Systems/RealInputHandler.h>

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();

    Window window;
    GameSettings settings;
    EntityManager entityManager;
    RealInputHandler inputHandler;

    sf::Clock clock;

    std::vector<entt::entity> active_entity;
};