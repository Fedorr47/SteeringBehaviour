#include <iostream>
#include <Game/Game.h>
#include "ThirdParty/entt/entt.hpp"
#include "ThirdParty/imgui/imgui-SFML.h"

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

int main(int argc, char** argv)
{
    StartGame();
    return 0;
}