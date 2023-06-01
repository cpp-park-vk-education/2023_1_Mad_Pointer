#include "game_loop.h"
#include "logger.h"

using namespace sf;
void GamеStart() {
    RenderWindow Play(VideoMode::getDesktopMode(), L"Уровень 1", Style::Fullscreen);

    RectangleShape background_play(Vector2f(1920, 1080));

    Texture texture;
    if (!texture.loadFromFile("image.jpg")) exit(1);
    background_play.setTexture(&texture);

    while (Play.isOpen()) {
        Event event_play;
        while (Play.pollEvent(event_play)) {
            if (event_play.type == Event::KeyPressed)
            {
                if (event_play.key.code == Keyboard::Escape) { Play.close(); }
            }
        }
        Play.clear();
        Play.draw(background_play);
        Play.display();
    }
}

int main() {
    //GamеStart();
    GameLoop gameLoop("The Floors");
    LOG_INFO("game loop created.");

    gameLoop.initializeSFML();
    gameLoop.initializeECS();
    gameLoop.run();
    return 0;
}
