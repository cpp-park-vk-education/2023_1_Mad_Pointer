#include "game_loop.h"

constexpr float DELTA_TIME_STEP = 1000 / 60;

void GameLoop::Run() {
    m_isRunning = true;
    while (m_isRunning) {
        ProcessWindowEvent();

        m_engine.update(DELTA_TIME_STEP);
    }
}

void GameLoop::InitializeSDL(int width, int height) {
        SDL_Init(SDL_INIT_VIDEO);
        m_window = SDL_CreateWindow(m_gameName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_FULLSCREEN_DESKTOP);

        if (!m_window) {
            LOG_ERROR("Window has not been created! Fatal!");
        }
}

void GameLoop::InitializeECS() {

}


