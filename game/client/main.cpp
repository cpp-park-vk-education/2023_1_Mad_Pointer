#include <iostream>

int main(int argc, char** argv) {

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

    return 0;
}