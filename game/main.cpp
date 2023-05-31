#include "game_loop.h"
#include "logger.h"

int main() {
    GameLoop gameLoop("The Floors");
    LOG_INFO("game loop created.");

    gameLoop.initializeSFML();
    gameLoop.initializeECS();
    gameLoop.run();
    return 0;
}
