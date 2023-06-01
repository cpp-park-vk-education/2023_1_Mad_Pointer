#include "shooter_game.h"
#include "cars_game.h"
#include "logger.h"
#include "menu/include/menu.h"

int main() {
    start();
    /*{
        GameLoopShooter gameLoop("The Floors", "image/image.jpg");
        LOG_INFO("Shooter game created");

        gameLoop.initializeSFML();
        gameLoop.initializeECS();
        gameLoop.run();
    }

    {
        GameLoopCars gameLoop("The Floors", "image/image.jpg");
        LOG_INFO("Cars game created");

        gameLoop.initializeSFML();
        gameLoop.initializeECS();
        gameLoop.run();
    }
    */
    return 0;
}
