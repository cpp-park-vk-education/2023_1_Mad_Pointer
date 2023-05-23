#include "game_loop.h"
#include "logger.h"

int main() {
    GameLoop gameLoop("The Floors");
    gameLoop.Run();

    LOG_WARN("hello");
    LOG_ERROR("error");
    return 0;
}
