#include "game_loop.h"
#include "render_system.h"

constexpr float DELTA_TIME_STEP = 1000 / 60;

void GameLoop::run() {
    m_isRunning = true;
    while (m_isRunning) {
        ProcessWindowEvent();
        m_engine.update(DELTA_TIME_STEP);
    }
}

void GameLoop::initializeSFML(int width, int height) {
        SDL_Init(SDL_INIT_VIDEO);
        m_window = SDL_CreateWindow(m_gameName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_FULLSCREEN_DESKTOP);

        if (!m_window) {
            LOG_ERROR("Window has not been created! Fatal!");
        }
}

void GameLoop::processWindowEvent() {
    SDL_PumpEvents();

    SDL_Event event;
    while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_SYSWMEVENT)) {
        switch (event.window.event) {
            case SDL_WINDOWEVENT_CLOSE:
                m_isRunning = false;
                return;
            default:
                return;
        }
    }
}

void GameLoop::initializeECS() {
    m_engine.getSystemManager()->addSystem<>
}


