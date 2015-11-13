#include <SFML/Window.hpp>

#include "Deck.h"
#include "Hand.h"

int main(int, char**) {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Black Jack");
    sf::Texture t_background;
    t_background.loadFromFile("res/table.png");
    sf::Sprite background;
    background.setTexture(t_background);

    typedef enum {
        MainMenu,
        Game,
        FinalMenu
    } GameState;

    GameState gameState = GameState::Game;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        window.clear(sf::Color::Black);

        switch (gameState) {

            case GameState::MainMenu:
                break;
            case GameState::Game:
                window.draw(background);
                break;
            case GameState::FinalMenu:
                break;

        }
    }

    return 0;
}