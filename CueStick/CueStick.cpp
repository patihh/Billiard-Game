#include "CueStick.hpp"
#include <cmath>

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