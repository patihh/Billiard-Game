#include "Table.hpp"
#include <cmath>

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

bool Table::isBallInPocket(const sf::Vector2f& ballPosition, float ballRadius) const {
    for (int i = 0; i < 6; ++i) {
        sf::Vector2f delta = ballPosition - pockets[i].getPosition();
        float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
        if (distance < pockets[i].getRadius() + ballRadius) {
            return true; // Bola berada di kantong
        }
    }
    return false;
}