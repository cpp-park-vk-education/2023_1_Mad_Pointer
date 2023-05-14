#include <iostream>
#include "vector2.h"

Game* g_GameInstance = new Game(GAME_TITLE);

int main(int argc, const char* args[]) {
    // initialize game
    g_GameInstance->Initialize(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, GAME_WINDOW_FULLSCREEN);

    // enter game main-loop
    g_GameInstance->Run();

    delete g_GameInstance;
    g_GameInstance = nullptr;

    // Vect2 v1{10, 20};
    // Vect2 v2{15, 1.5};
    // Vect2 v3 = v1 - v2;
    // std::cout << v3.x << " " << v3.y << "\n";
    // std::cout << (v1 == v2) << "\n";

    return 0;
}
