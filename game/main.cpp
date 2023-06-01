#include "shooter_game.h"
#include "logger.h"


int main() {
    {
        GameLoopShooter gameLoop("The Floors", "image/image.jpg");
        LOG_INFO("game loop created.");

        gameLoop.initializeSFML();
        gameLoop.initializeECS();
        gameLoop.run();
    }

    {

    }

    return 0;
}
