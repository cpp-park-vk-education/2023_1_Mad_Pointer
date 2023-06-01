#include "game_loop.h"
#include "logger.h"
#include "menu/include/menu.h"

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

void InitText(Text& mtext,
              float xpos,
              float ypos,
              String str,
              int size_font = 60,
              Color menu_text_color = Color::White,
              int bord = 0,
              Color border_color = Color::Black);

int main() {
    RenderWindow window;
    window.create(VideoMode::getDesktopMode(), L"Моя игра", Style::Fullscreen);

    window.setMouseCursorVisible(false);
    float width = VideoMode::getDesktopMode().width;
    float height = VideoMode::getDesktopMode().height;

    RectangleShape background(Vector2f(width, height));
    Texture texture_window;
    if (!texture_window.loadFromFile("image/menu_background.jpg")) return 4;
    background.setTexture(&texture_window);

    Font font;
    if (!font.loadFromFile("font/MyriadPro.otf")) return 5;
    Text title;
    title.setFont(font);

    InitText(title, 480, 50, L"Maddest Pointer", 150, Color(237, 147, 0), 3);
    String name_menu[]{L"Стрелялка", L"Машинки", L"Выход"};

    GameMenu menu(window, 950, 350, 3, name_menu, 100, 120);
    menu.setMenuTextColor(Color(237, 147, 0), Color::Red, Color::Black);
    menu.alignMenuPosition(2);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Up) {
                    menu.moveUp();
                }
                if (event.key.code == Keyboard::Down) {
                    menu.moveDown();
                }
                if (event.key.code == Keyboard::Return) {
                    switch (menu.getNumOfSelectedItem()) {
                        case 0:
                            std::cout << "start first game" << std::endl;
                            break;
                        case 1:
                            std::cout << "start second game" << std::endl;
                            break;
                        case 2:
                            window.close();
                            break;
                    }
                }
            }
        }
        window.clear();
        window.draw(background);
        window.draw(title);
        menu.draw();
        window.display();
    }

    //GamеStart();
    // GameLoop gameLoop("The Floors");
    // LOG_INFO("game loop created.");

    // gameLoop.initializeSFML();
    // gameLoop.initializeECS();
    // gameLoop.run();
    return 0;
}

void InitText(Text& mtext, float xpos, float ypos, String str, int size_font, Color menu_text_color, int bord, Color border_color) {
    mtext.setCharacterSize(size_font);
    mtext.setPosition(xpos, ypos);
    mtext.setString(str);
    mtext.setFillColor(menu_text_color);
    mtext.setOutlineThickness(bord);
    mtext.setOutlineColor(border_color);
}
