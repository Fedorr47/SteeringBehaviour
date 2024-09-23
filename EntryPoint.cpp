#include <Game/Game.h>
#include "entt/entt.hpp"
#include <iostream>

void StartGame()
{
    try {
        Game game;
        game.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown exception caught!" << std::endl;
    }
}

int main()
{
    StartGame();
    return 0;
}