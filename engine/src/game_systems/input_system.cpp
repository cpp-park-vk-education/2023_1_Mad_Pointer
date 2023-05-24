#include "input_system.h"

#include "SDL.h"

void InputSystem::preUpdate(float deltaTime) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                // quit
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    // mouse clicked
                }
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        // quit
                        break;
                    case SDLK_w:
                        // pressed w
                        break;
                    case SDLK_s:
                        // pressed s
                        break;
                    case SDLK_a:
                        // pressed a
                        break;
                    case SDLK_d:
                        // pressed d
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                        // released w
                        break;
                    case SDLK_s:
                        // released w
                        break;
                    case SDLK_a:
                        // released w
                        break;
                    case SDLK_d:
                        // released w
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}
