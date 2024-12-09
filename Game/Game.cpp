#include "Game.hpp"

Game::Game()
    : table(1100.0f, 600.0f, 40.0f, 25.0f),
      whiteBall(18.0f, sf::Color::White, false, {275.0f, 300.0f}, {200.0f, 150.0f}),
      cueStick(450.0f, 12.0f, {275.0f - 450.0f - 10, 300.0f}) {
    setupBalls();
}

void Game::setupBalls() {
    float startX = 3 * 1100.0f / 4; // Posisi horizontal awal formasi
    float startY = 600.0f / 2;   // Posisi vertikal tengah meja
    int rows = 5; // Jumlah baris bola dalam formasi segitiga

    // Warna untuk bola solid dan striped
    sf::Color colors[15] = {
        sf::Color(255, 255, 0),   // Bola 1 (kuning)
        sf::Color(0, 0, 255),     // Bola 2 (biru)
        sf::Color(255, 0, 0),     // Bola 3 (merah)
        sf::Color(128, 0, 128),   // Bola 4 (ungu)
        sf::Color(255, 165, 0),   // Bola 5 (oranye)
        sf::Color(0, 255, 0),     // Bola 6 (hijau)
        sf::Color(128, 0, 0),     // Bola 7 (maroon)
        sf::Color(0, 0, 0),       // Bola 8 (hitam)
        sf::Color(255, 255, 0),   // Bola 9 (kuning stripe)
        sf::Color(0, 0, 255),     // Bola 10 (biru stripe)
        sf::Color(255, 0, 0),     // Bola 11 (merah stripe)
        sf::Color(128, 0, 128),   // Bola 12 (ungu stripe)
        sf::Color(255, 165, 0),   // Bola 13 (oranye stripe)
        sf::Color(0, 255, 0),     // Bola 14 (hijau stripe)
        sf::Color(128, 0, 0)      // Bola 15 (maroon stripe)
    };

    int colorIndex = 0; // Indeks warna

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= i; j++) {
            // Tentukan apakah bola tersebut solid atau striped
            bool isStriped = (colorIndex >= 8); // Bola 9-15 adalah striped

            // Tentukan posisi bola
            float x = startX + i * BALL_RADIUS * 2.0f; // Jarak horizontal antar baris
            float y = startY - i * BALL_RADIUS + j * BALL_RADIUS * 2.0f; // Jarak vertikal antar bola

            // Tambahkan bola ke dalam vektor
            balls.emplace_back(BALL_RADIUS, colors[colorIndex % 15], isStriped, sf::Vector2f(x, y), sf::Vector2f(0.0f, 0.0f));

            colorIndex++;
        }
    }
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