#pragma once
#include "shooter_game.h"
#include "cars_game.h"

#include <SFML/Graphics.hpp>

namespace menu {
class GameMenu {
public:
    GameMenu(sf::RenderWindow& window, float menuX, float menuY, int numOfItems, sf::String name[], int fontSize = 60, int stepBetweenItems = 80);
    ~GameMenu() { delete[] m_menuItemNames; }

    void setTextObjOfMenuItems(sf::Text& textObj, sf::String menuItemText, float posX, float posY);
    void setMenuTextColor(sf::Color itemsTextColor, sf::Color selectedItemColor, sf::Color itemsBorderColor);
    void alignMenuPosition(int posX);

    void moveUp();
    void moveDown();
    void draw();
    int getNumOfSelectedItem() { return m_selectedItem; }

private:
    sf::RenderWindow& m_window;

    float m_menuPosX;
    float m_menuPosY;
    int m_stepBetweenItems;
    int m_maxNumberOfItems;
    int m_fontSize;
    int m_selectedItem;
    
    sf::Font font;
    sf::Text* m_menuItemNames;
    sf::Color m_itemsTextColor = sf::Color::White;
    sf::Color m_itemsBorderColor = sf::Color::Black;
    sf::Color m_selectedItemColor = sf::Color::Yellow;
};

GameMenu::GameMenu(sf::RenderWindow& window, float menuX, float menuY, int numOfItems, sf::String name[], int fontSize, int stepBetweenItems)
    : m_window(window), m_menuPosX(menuX), m_menuPosY(menuY), m_fontSize(fontSize), m_stepBetweenItems(stepBetweenItems) {

    if (!font.loadFromFile("font/MyriadPro.otf")) exit(32);
    m_maxNumberOfItems = numOfItems;
    m_menuItemNames = new sf::Text[m_maxNumberOfItems];

    for (int i = 0, yPos = m_menuPosY; i < m_maxNumberOfItems; ++i, yPos += m_stepBetweenItems) {
        setTextObjOfMenuItems(m_menuItemNames[i], name[i], m_menuPosX, yPos);
    }

    m_selectedItem = 0;
    m_menuItemNames[m_selectedItem].setFillColor(m_selectedItemColor);
}

void GameMenu::setTextObjOfMenuItems(sf::Text& textObj, sf::String menuItemText, float posX, float posY) {
    textObj.setFont(font);
    textObj.setFillColor(m_itemsTextColor);
    textObj.setString(menuItemText);
    textObj.setCharacterSize(m_fontSize);
    textObj.setPosition(posX, posY);
    textObj.setOutlineThickness(1);
    textObj.setOutlineColor(m_itemsBorderColor);
}

void GameMenu::setMenuTextColor(sf::Color itemsTextColor, sf::Color selectedItemColor, sf::Color itemsBorderColor) {
    m_itemsTextColor = itemsTextColor;
    m_selectedItemColor = selectedItemColor;
    m_itemsBorderColor = itemsBorderColor;

    for (int i = 0; i < m_maxNumberOfItems; ++i) {
        m_menuItemNames[i].setFillColor(m_itemsTextColor);
        m_menuItemNames[i].setOutlineColor(m_itemsBorderColor);
    }
    m_menuItemNames[m_selectedItem].setFillColor(m_selectedItemColor);
}

void GameMenu::alignMenuPosition(int posX) {
    float nullx = 0;
    for (int i = 0; i < m_maxNumberOfItems; ++i) {
        switch (posX) {
            case 0:
                nullx = 0;
                break;
            case 1:
                nullx = m_menuItemNames[i].getLocalBounds().width;
                break;
            case 2:
                nullx = nullx = m_menuItemNames[i].getLocalBounds().width / 2;
                break;
        }
        m_menuItemNames[i].setPosition(m_menuItemNames[i].getPosition().x - nullx, m_menuItemNames[i].getPosition().y);
    }
}

void GameMenu::moveUp() {
    --m_selectedItem;
    if (m_selectedItem >= 0) {
        m_menuItemNames[m_selectedItem].setFillColor(m_selectedItemColor);
        m_menuItemNames[m_selectedItem + 1].setFillColor(m_itemsTextColor);
    } else {
        m_menuItemNames[0].setFillColor(m_itemsTextColor);
        m_selectedItem = m_maxNumberOfItems - 1;
        m_menuItemNames[m_selectedItem].setFillColor(m_selectedItemColor);
    }
}

void GameMenu::moveDown() {
    ++m_selectedItem;
    if (m_selectedItem < m_maxNumberOfItems) {
        m_menuItemNames[m_selectedItem - 1].setFillColor(m_itemsTextColor);
        m_menuItemNames[m_selectedItem].setFillColor(m_selectedItemColor);
    } else {
        m_menuItemNames[m_maxNumberOfItems - 1].setFillColor(m_itemsTextColor);
        m_selectedItem = 0;
        m_menuItemNames[m_selectedItem].setFillColor(m_selectedItemColor);
    }
}

void GameMenu::draw() {
    for (int i = 0; i < m_maxNumberOfItems; i++) {
        m_window.draw(m_menuItemNames[i]);
    }
}

void initText(sf::Text& textObj,
              float xpos,
              float ypos,
              sf::String text,
              int fontSize = 60,
              int borderThickness = 0,
              sf::Color menuTextColor = sf::Color::White,
              sf::Color borderColor = sf::Color::Black) {
    textObj.setCharacterSize(fontSize);
    textObj.setPosition(xpos, ypos);
    textObj.setString(text);
    textObj.setOutlineThickness(borderThickness);
    textObj.setFillColor(menuTextColor);
    textObj.setOutlineColor(borderColor);
}

void start() {
    sf::RenderWindow window;
    window.create(sf::VideoMode::getDesktopMode(), L"Моя игра", sf::Style::Fullscreen);

    window.setMouseCursorVisible(false);
    float width = sf::VideoMode::getDesktopMode().width;
    float height = sf::VideoMode::getDesktopMode().height;

    sf::RectangleShape background(sf::Vector2f(width, height));
    sf::Texture texture_window;
    if (!texture_window.loadFromFile("image/menu_background.jpg")) { exit(5); }
    background.setTexture(&texture_window);

    sf::Font font;
    if (!font.loadFromFile("font/MyriadPro.otf")) { exit(5); }
    sf::Text title;
    title.setFont(font);

    initText(title, 450, 50, L"Maddest Pointer", 150, 1, sf::Color(237, 100, 0), sf::Color(100, 100, 100));
    sf::String name_menu[]{L"Стрелялка", L"Машинки", L"Выход"};

    GameMenu menu(window, 950, 350, 3, name_menu, 100, 120);
    menu.setMenuTextColor(sf::Color(100, 100, 100), sf::Color::White, sf::Color(60, 60, 60));
    menu.alignMenuPosition(2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Up) {
                    menu.moveUp();
                }
                if (event.key.code == sf::Keyboard::Down) {
                    menu.moveDown();
                }
                if (event.key.code == sf::Keyboard::Return) {
                    switch (menu.getNumOfSelectedItem()) {
                        case 0:
                            {
                                GameLoopShooter gameLoop("The Floors", "image/image.jpg");
                                LOG_INFO("Shooter game created");
                                gameLoop.initializeSFML();
                                gameLoop.initializeECS();
                                gameLoop.run();
                            }
                            break;
                        case 1:
                            {
                                GameLoopCars gameLoop("The Floors", "image/cars_background.png");
                                LOG_INFO("Cars game created");
                                gameLoop.initializeSFML();
                                gameLoop.initializeECS();
                                gameLoop.run();
                            }
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
}
}