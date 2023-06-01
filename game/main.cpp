#include "shooter_game.h"
#include "cars_game.h"
#include "logger.h"


int main() {
    /*{
        GameLoopShooter gameLoop("The Floors", "image/image.jpg");
        LOG_INFO("Shooter game created");

        gameLoop.initializeSFML();
        gameLoop.initializeECS();
        gameLoop.run();
    }*/

    {
        GameLoopCars gameLoop("The Floors", "image/image.jpg");
        LOG_INFO("Cars game created");

        gameLoop.initializeSFML();
        gameLoop.initializeECS();
        gameLoop.run();
    }

    return 0;
}
