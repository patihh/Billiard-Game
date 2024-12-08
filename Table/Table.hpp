#ifndef TABLE_HPP
#define TABLE_HPP

#include <SFML/Graphics.hpp>

class Table {
private:
    sf::RectangleShape surface;
    sf::RectangleShape borders[4];
    sf::CircleShape pockets[6];

public:
    Table(float width, float height, float borderThickness, float pocketRadius);

    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;
};

#endif