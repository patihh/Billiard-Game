#ifndef CUESTICK_HPP
#define CUESTICK_HPP

#include <SFML/Graphics.hpp>

class CueStick {
private:
    sf::RectangleShape stick;

public:
    CueStick(float length, float thickness, const sf::Vector2f& position);
    void update(const sf::Vector2i& mousePos);
    void draw(sf::RenderWindow& window) const;
};

#endif