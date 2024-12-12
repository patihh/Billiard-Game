#include "Game.hpp"
#include <cmath>

Game::Game()
    : table(1100.0f, 600.0f, 40.0f, 25.0f),
      whiteBall(18.0f, sf::Color::White, false, {275.0f, 300.0f}, {0.0f, 0.0f}),
      cueStick(450.0f, 12.0f, {275.0f, 300.0f}) {
    setupBalls();
}

void Game::setupBalls() {
    float startX = 3 * 1100.0f / 4; // Posisi horizontal awal formasi
    float startY = 600.0f / 2;   // Posisi vertikal tengah meja
    int rows = 5; // Jumlah baris bola dalam formasi segitiga

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

    int colorIndex = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= i; j++) {
            bool isStriped = (colorIndex >= 8);
            float x = startX + i * BALL_RADIUS * 2.0f;
            float y = startY - i * BALL_RADIUS + j * BALL_RADIUS * 2.0f;
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
    handleCollisions();

    // Get mouse position
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    
    // Update cue stick direction
    cueStick.update(mousePos, whiteBall.getPosition());

    // Handle shot strength and hitting the white ball
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        // Calculate direction and strength (magnitude) of the shot
        sf::Vector2f direction = sf::Vector2f(mousePos) - whiteBall.getPosition();
        float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (magnitude > 0) {
            direction /= magnitude;  // Normalize the direction

            // Set the velocity of the white ball based on the mouse drag (strength)
            whiteBall.setVelocity(direction * magnitude * 0.5f);  // Multiply by a factor for strength
        }
    }

    // Check if the white ball has stopped
    if (whiteBall.getVelocity() == sf::Vector2f(0.0f, 0.0f)) {
        cueStick.setVisible(true); // Show cue stick when the ball stops
    } else {
        cueStick.setVisible(false); // Hide cue stick while the ball is moving
    }
}

void Game::draw(sf::RenderWindow& window) {
    table.draw(window);
    whiteBall.draw(window);
    for (const auto& ball : balls) {
        ball.draw(window);
    }
    cueStick.draw(window);
}

void Game::handleCollisions() {
    for (size_t i = 0; i < balls.size(); ++i) {
        for (size_t j = i + 1; j < balls.size(); ++j) {
            checkCollision(balls[i], balls[j]);
        }
        checkCollision(whiteBall, balls[i]);
        
        // Check if the white ball or any other ball enters a pocket
        if (checkPockets(balls[i])) {
            balls[i].setPosition(randomPocketPosition());
            balls[i].setVelocity(sf::Vector2f(0.0f, 0.0f)); // Stop the ball
        }
    }

    if (checkPockets(whiteBall)) {
        whiteBall.setPosition(randomPocketPosition()); // Player can place the ball after it falls in the pocket
        whiteBall.setVelocity(sf::Vector2f(0.0f, 0.0f)); // Stop the ball
    }
}

sf::Vector2f Game::randomPocketPosition() {
    // Return a random position near one of the pockets on the table
    // You can randomize this based on the pockets' positions.
    int pocketIndex = rand() % 6;
    return table.getPocketPosition(pocketIndex);
}

bool Game::checkCollision(Ball& ball1, Ball& ball2) {
    sf::Vector2f delta = ball2.getPosition() - ball1.getPosition();
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    if (distance < BALL_RADIUS * 2.0f) {
        // Collision detected, calculate response
        sf::Vector2f normal = delta / distance; // Normalized collision vector
        sf::Vector2f relativeVelocity = ball2.getVelocity() - ball1.getVelocity();
        float speed = relativeVelocity.x * normal.x + relativeVelocity.y * normal.y;

        // Elastic collision formula (simplified)
        if (speed < 0) {
            float restitution = 0.9f; // Coefficient of restitution
            float impulse = 2 * speed / (1.0f / BALL_RADIUS + 1.0f / BALL_RADIUS);
            sf::Vector2f impulseVector = normal * impulse;

            ball1.setVelocity(ball1.getVelocity() + impulseVector / BALL_RADIUS);
            ball2.setVelocity(ball2.getVelocity() - impulseVector / BALL_RADIUS);
        }
    }
    return false;
}

bool Game::checkPockets(Ball& ball) {
    return table.isBallInPocket(ball.getPosition(), BALL_RADIUS);
}