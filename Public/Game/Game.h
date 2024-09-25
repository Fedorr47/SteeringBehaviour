#pragma once
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
    GameSettings settings;
    EntityManager entityManager;
    RealInputHandler inputHandler;

    sf::Clock clock;

    std::vector<entt::entity> active_entity;

    bool limitFPS;
    unsigned int maxFPS;

    float currentFPS = 60.0f;
    float fps;
};