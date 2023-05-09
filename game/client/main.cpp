#include <iostream>
#include <SDL.h>

int main(int argc, char** argv) {
    /*SDL_Renderer* renderer ();
    World* world = World::createWorld();

    EntitySystem* testSystem = world->registerSystem(new TestSystem());

    Entity* ent = world->create();
    auto pos = ent->assign<Position>(0.f, 0.f);
    auto rot = ent->assign<Rotation>(0.f);

    std::cout << "Initial values: position(" << pos->x << ", " << pos->y << "), rotation(" << rot->angle << ")" << std::endl;

    world->tick(10.f);

    std::cout << "After tick(10): position(" << pos->x << ", " << pos->y << "), rotation(" << rot->angle << ")" << std::endl;

    world->disableSystem(testSystem);

    world->tick(10.f);

    std::cout << "After tick(10) and DisableSystem(testSystem): position(" << pos->x << ", " << pos->y << "), rotation(" << rot->angle << ")" << std::endl;

    world->enableSystem(testSystem);

    world->tick(10.f);

    std::cout << "After tick(10) and EnableSystem(testSystem): position(" << pos->x << ", " << pos->y << "), rotation(" << rot->angle << ")" << std::endl;

    ent->remove<Position>();
    ent->remove<Rotation>();

    std::cout << "Creating more entities..." << std::endl;

    for (int i = 0; i < 10; ++i)
    {
        ent = world->create();
        ent->assign<SomeComponent>();
    }

    int count = 0;
    std::cout << "Counting entities with SomeComponent..." << std::endl;
    // range based for loop
    for (auto ent : world->each<SomeComponent>())
    {
        ++count;
        std::cout << "Found entity #" << ent->getEntityId() << std::endl;
    }
    std::cout << count << " entities have SomeComponent!" << std::endl;

    // Emitting events
    world->emit<SomeEvent>({ 4 });

    std::cout << "We have " << world->getCount() << " entities right now." << std::endl;
    world->cleanup();
    std::cout << "After a cleanup, we have " << world->getCount() << " entities." << std::endl;

    std::cout << "Destroying the world..." << std::endl;

    world->destroyWorld();

    std::cout << "Press any key to exit..." << std::endl;
    std::getchar();

    return 0; */
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
        return 1;
    }
    SDL_Window *win = SDL_CreateWindow("Rendering to a texture!", SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED, 400, 600, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1,
                                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

    //Put your own bmp image here
    SDL_Surface *bmpSurf = SDL_LoadBMP("../res/image.bmp");
    SDL_Texture *bmpTex = SDL_CreateTextureFromSurface(renderer, bmpSurf);
    SDL_FreeSurface(bmpSurf);

    //Make a target texture to render too
    SDL_Texture *texTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                               SDL_TEXTUREACCESS_TARGET, 400, 600);

    //Now render to the texture
    SDL_SetRenderTarget(renderer, texTarget);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, bmpTex, NULL, NULL);
    //Detach the texture
    SDL_SetRenderTarget(renderer, NULL);

    //Now render the texture target to our screen, but upside down
    SDL_RenderClear(renderer);
    SDL_RenderCopyEx(renderer, texTarget, NULL, NULL, 0, NULL, SDL_FLIP_VERTICAL);
    SDL_RenderPresent(renderer);

    SDL_Delay(1000);
    SDL_DestroyTexture(texTarget);
    SDL_DestroyTexture(bmpTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
