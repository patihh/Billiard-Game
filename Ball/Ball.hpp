#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>

class Ball {
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    bool isStriped;

public:
    Ball(float radius, const sf::Color& color, bool striped, const sf::Vector2f& position, const sf::Vector2f& initialVelocity);

    void update(float deltaTime, const sf::FloatRect& tableBounds);
    void draw(sf::RenderWindow& window) const;

    sf::Vector2f getPosition() const;
    void setVelocity(const sf::Vector2f& vel);
    bool getIsStriped() const;
};

#endif