#include "CueStick.hpp"
#include <cmath>

CueStick::CueStick(float length, float thickness, const sf::Vector2f& position)
    : originalPosition(position), isPullingBack(false) {
    stick.setSize(sf::Vector2f(length, thickness));
    stick.setFillColor(sf::Color(139, 69, 19));
    stick.setOrigin(0, thickness / 2);
    stick.setPosition(position);
}

void CueStick::update(const sf::Vector2i& mousePos, bool isMousePressed) {
    // Jika mouse ditekan, tarik mundur cue stick
    if (isMousePressed) {
        isPullingBack = true;
    } else if (!isMousePressed && isPullingBack) {
        // Jika mouse dilepas, reset posisi cue stick dan pukul bola
        isPullingBack = false;
    }

    if (isPullingBack) {
        // Menggerakkan cue stick mundur berdasarkan posisi mouse
        float distance = std::sqrt(std::pow(mousePos.x - originalPosition.x, 2) + std::pow(mousePos.y - originalPosition.y, 2));
        stick.setPosition(originalPosition.x - distance / 2, originalPosition.y);  // Mengatur mundur cue stick
    } else {
        // Saat tidak mundur, cue stick kembali ke posisi semula
        stick.setPosition(originalPosition);
    }

    // Update rotasi cue stick ke arah mouse
    sf::Vector2f direction = sf::Vector2f(mousePos) - stick.getPosition();
    float angle = std::atan2(direction.y, direction.x);
    stick.setRotation(angle * 180 / 3.14159f);
}

void CueStick::draw(sf::RenderWindow& window) const {
    window.draw(stick);  // Gambar cue stick ke window
}

void CueStick::resetPosition() {
    stick.setPosition(originalPosition);  // Kembalikan posisi cue stick ke posisi awal
}

sf::Vector2f CueStick::getPosition() const {
    return stick.getPosition();
}

sf::Vector2f CueStick::getOriginalPosition() const {
    return originalPosition;  // Mengembalikan posisi asli cue stick
}