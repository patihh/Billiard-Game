#include "Ball.hpp"

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
    // Update bola
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