#pragma once
#include <memory>

#include "Window/Window.h"
#include "EntityManager/EntityManager.h"
#include "Settings/GameSettings.h"
#include <Systems/RealInputHandler.h>

class Game
{
public:
    Game();
    ~Game();
    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render(sf::Time deltaTime);

    Window window;
    std::unique_ptr<GameSettings> settings;
    std::unique_ptr<EntityManager> entityManager;
    std::unique_ptr<GameInputHandler> inputHandler;

    sf::Clock clock;

    std::vector<entt::entity> active_entity;

    float currentFPS = 60.0f;
    float fps = 0.0f;
};