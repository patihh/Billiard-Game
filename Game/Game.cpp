#include "Game.hpp"

Game::Game()
    : table(1100.0f, 600.0f, 40.0f, 25.0f),
      whiteBall(18.0f, sf::Color::White, false, {275.0f, 300.0f}, {200.0f, 150.0f}),
      cueStick(450.0f, 12.0f, {275.0f - 450.0f - 10, 300.0f}) {
    setupBalls();
}

void Game::setupBalls() {
    // Setup bola
}

void Game::update(float deltaTime, const sf::RenderWindow& window) {
    whiteBall.update(deltaTime, table.getBounds());
    for (auto& ball : balls) {
        ball.update(deltaTime, table.getBounds());
    }
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    cueStick.update(mousePos);
}

void Game::draw(sf::RenderWindow& window) {
    table.draw(window);
    whiteBall.draw(window);
    for (const auto& ball : balls) {
        ball.draw(window);
    }
    cueStick.draw(window);
}