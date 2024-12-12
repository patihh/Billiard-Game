#ifndef CUESTICK_HPP
#define CUESTICK_HPP

#include <SFML/Graphics.hpp>

class CueStick {
private:
    sf::RectangleShape stick;
    bool isVisible; // To control the visibility of the cue stick

public:
    CueStick(float length, float thickness, const sf::Vector2f& position);
    void update(const sf::Vector2i& mousePos, const sf::Vector2f& ballPos);
    void draw(sf::RenderWindow& window) const;
    void setVisible(bool visible); // To toggle the cue stick's visibility
};

#endif