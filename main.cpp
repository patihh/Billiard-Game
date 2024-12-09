#include "Game/Game.hpp"
#include <SFML/Graphics.hpp>



int main() {
    sf::RenderWindow window(sf::VideoMode(1100, 600), "Billiard Game");
    Game game;

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        game.update(deltaTime.asSeconds(), window);

        window.clear();
        game.draw(window);
        window.display();
    }

    return 0;
}