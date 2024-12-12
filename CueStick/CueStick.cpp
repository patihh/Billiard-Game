#include "CueStick.hpp"
#include <cmath>

CueStick::CueStick(float length, float thickness, const sf::Vector2f& position)
    : isVisible(true) { // Default to visible
    stick.setSize(sf::Vector2f(length, thickness));
    stick.setFillColor(sf::Color(139, 69, 19));
    stick.setOrigin(0, thickness / 2);
    stick.setPosition(position);
}

void CueStick::update(const sf::Vector2i& mousePos, const sf::Vector2f& ballPos) {
    if (!isVisible) return;

    sf::Vector2f direction = sf::Vector2f(mousePos) - ballPos; // Direction from the white ball to the mouse
    float angle = std::atan2(direction.y, direction.x); // Calculate the angle
    stick.setRotation(angle * 180 / 3.14159f); // Set the rotation of the cue stick
}

void CueStick::draw(sf::RenderWindow& window) const {
    if (isVisible) {
        window.draw(stick);
    }
}

void CueStick::setVisible(bool visible) {
    isVisible = visible;
}