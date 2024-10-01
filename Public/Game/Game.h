#pragma once
#include <memory>

#include "Window/Window.h"
#include "ThirdParty/entt/entt.hpp"


struct GameSettings;
class EntityManager;
class GameInputHandler;
class ObjectManager;
class DebugInfo;

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
    std::unique_ptr<ObjectManager> objectManager;

    std::shared_ptr<DebugInfo> debugInfo;

    sf::Clock clock;

    std::vector<entt::entity> active_entity;

    float currentFPS = 60.0f;
};