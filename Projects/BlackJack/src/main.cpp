#include <SFML/Window.hpp>

int main() {
    sf::Window window(sf::VideoMode(800, 600), "Black Jack");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:break;
                case sf::Event::LostFocus:break;
                case sf::Event::GainedFocus:break;
                case sf::Event::TextEntered:break;
                case sf::Event::KeyPressed:break;
                case sf::Event::KeyReleased:break;
                case sf::Event::MouseWheelMoved:break;
                case sf::Event::MouseWheelScrolled:break;
                case sf::Event::MouseButtonPressed:break;
                case sf::Event::MouseButtonReleased:break;
                case sf::Event::MouseMoved:break;
                case sf::Event::MouseEntered:break;
                case sf::Event::MouseLeft:break;
                case sf::Event::JoystickButtonPressed:break;
                case sf::Event::JoystickButtonReleased:break;
                case sf::Event::JoystickMoved:break;
                case sf::Event::JoystickConnected:break;
                case sf::Event::JoystickDisconnected:break;
                case sf::Event::TouchBegan:break;
                case sf::Event::TouchMoved:break;
                case sf::Event::TouchEnded:break;
                case sf::Event::SensorChanged:break;
                case sf::Event::Count:break;
            }
        }
    }

    return 0;
}