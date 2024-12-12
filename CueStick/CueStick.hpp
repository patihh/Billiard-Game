#ifndef CUESTICK_HPP
#define CUESTICK_HPP

#include <SFML/Graphics.hpp>

class CueStick {
private:
    sf::RectangleShape stick;
    sf::Vector2f originalPosition;  // Posisi awal cue stick
    bool isPullingBack;  // Apakah cue stick sedang mundur

public:
    CueStick(float length, float thickness, const sf::Vector2f& position);
    void update(const sf::Vector2i& mousePos, bool isMousePressed);
    void draw(sf::RenderWindow& window) const;
    void resetPosition();  // Reset posisi cue stick
    sf::Vector2f getPosition() const;
    sf::Vector2f getOriginalPosition() const;  // Getter untuk posisi asli
};

#endif