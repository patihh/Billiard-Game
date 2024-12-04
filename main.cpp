#include <SFML/Graphics.hpp>
#include "main.hpp"

// === Implementasi Ball ===
Ball::Ball(float radius, const sf::Color& color, bool striped, const sf::Vector2f& position, const sf::Vector2f& initialVelocity)
    : isStriped(striped), velocity(initialVelocity) {
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setOrigin(radius, radius);
    shape.setPosition(position);

    if (isStriped) {
        shape.setOutlineThickness(5);
        shape.setOutlineColor(sf::Color::White);
    }
}

void Ball::update(float deltaTime, const sf::FloatRect& tableBounds) {
    shape.move(velocity * deltaTime);

    if (shape.getPosition().x <= tableBounds.left + shape.getRadius() ||
        shape.getPosition().x >= tableBounds.left + tableBounds.width - shape.getRadius()) {
        velocity.x = -velocity.x * 0.9f;
    }
    if (shape.getPosition().y <= tableBounds.top + shape.getRadius() ||
        shape.getPosition().y >= tableBounds.top + tableBounds.height - shape.getRadius()) {
        velocity.y = -velocity.y * 0.9f;
    }
}

void Ball::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::Vector2f Ball::getPosition() const {
    return shape.getPosition();
}

void Ball::setVelocity(const sf::Vector2f& vel) {
    velocity = vel;
}

bool Ball::getIsStriped() const {
    return isStriped;
}

// === Implementasi Table ===
Table::Table(float width, float height, float borderThickness, float pocketRadius) {
    // Setup surface
    surface.setSize(sf::Vector2f(width - 2 * borderThickness, height - 2 * borderThickness));
    surface.setFillColor(sf::Color(40, 119, 61)); // Warna hijau terang
    surface.setPosition(borderThickness, borderThickness);

    // Setup borders
    sf::Color borderColor(72, 63, 29); // Warna coklat untuk border
    borders[0].setSize(sf::Vector2f(width, borderThickness)); // Top border
    borders[0].setPosition(0, 0);
    borders[0].setFillColor(borderColor);

    borders[1].setSize(sf::Vector2f(width, borderThickness)); // Bottom border
    borders[1].setPosition(0, height - borderThickness);
    borders[1].setFillColor(borderColor);

    borders[2].setSize(sf::Vector2f(borderThickness, height)); // Left border
    borders[2].setPosition(0, 0);
    borders[2].setFillColor(borderColor);

    borders[3].setSize(sf::Vector2f(borderThickness, height)); // Right border
    borders[3].setPosition(width - borderThickness, 0);
    borders[3].setFillColor(borderColor);

    // Setup pockets
    float pocketPositions[6][2] = {
        {borderThickness - pocketRadius, borderThickness - pocketRadius},                                     // Kiri atas
        {width - borderThickness - pocketRadius, borderThickness - pocketRadius},                            // Kanan atas
        {borderThickness - pocketRadius, height - borderThickness - pocketRadius},                           // Kiri bawah
        {width - borderThickness - pocketRadius, height - borderThickness - pocketRadius},                   // Kanan bawah
        {width / 2 - pocketRadius, borderThickness - pocketRadius},                                          // Tengah atas
        {width / 2 - pocketRadius, height - borderThickness - pocketRadius}                                  // Tengah bawah
    };

    for (int i = 0; i < 6; i++) {
        pockets[i].setRadius(pocketRadius);
        pockets[i].setFillColor(sf::Color::Black);
        pockets[i].setPosition(pocketPositions[i][0], pocketPositions[i][1]);
    }
}

void Table::draw(sf::RenderWindow& window) const {
    window.draw(surface);
    for (const auto& border : borders) {
        window.draw(border);
    }
    for (const auto& pocket : pockets) {
        window.draw(pocket);
    }
}

sf::FloatRect Table::getBounds() const {
    return surface.getGlobalBounds();
}

// === Implementasi CueStick ===
CueStick::CueStick(float length, float thickness, const sf::Vector2f& position) {
    stick.setSize(sf::Vector2f(length, thickness));
    stick.setFillColor(sf::Color(139, 69, 19));
    stick.setOrigin(0, thickness / 2);
    stick.setPosition(position);
}

void CueStick::update(const sf::Vector2i& mousePos) {
    sf::Vector2f direction = sf::Vector2f(mousePos) - stick.getPosition();
    float angle = std::atan2(direction.y, direction.x);
    stick.setRotation(angle * 180 / 3.14159f);
}

void CueStick::draw(sf::RenderWindow& window) const {
    window.draw(stick);  // Gambar cue stick ke window
}

// === Implementasi Game ===
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

            sf::CircleShape ball(18.0f); // Radius bola
            ball.setFillColor(colors[colorIndex % 15]);
            ball.setOrigin(18.0f, 18.0f);  // Mengatur titik origin agar bola berpusat

            // Tentukan posisi bola
            float x = startX + i * 18.0f * 1.8f; // Jarak horizontal antar baris
            float y = startY - i * 18.0f + j * 18.0f * 2.0f; // Jarak vertikal antar bola
            ball.setPosition(x, y);

            balls.push_back(Ball(18.0f, colors[colorIndex % 15], isStriped, sf::Vector2f(x, y), sf::Vector2f(0.0f, 0.0f)));

            colorIndex++;
        }
    }
}

void Game::update(float deltaTime, const sf::RenderWindow& window) {
    // Update bola putih
    whiteBall.update(deltaTime, table.getBounds());

    // Update bola lainnya
    for (auto& ball : balls) {
        ball.update(deltaTime, table.getBounds());
    }

    // Update cue stick sesuai posisi mouse
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