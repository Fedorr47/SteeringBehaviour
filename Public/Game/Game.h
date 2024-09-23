#pragma once
#include "Player/Player.h"
#include "Window/Window.h"

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();

    Window window;
    Player player;
    sf::Clock clock;
};
