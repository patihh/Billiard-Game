#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Constants.hpp"

class Ball {
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    sf::Vector2f initialPosition; 
    bool isStriped; 

public:
    Ball(float radius, sf::Vector2f position, sf::Color color, int id)
        : velocity(0.0f, 0.0f), initialPosition(position), isStriped(false) {

        if (id >= 9 && id <= 15) {
            isStriped = true; 
        }

        shape.setRadius(radius);
        shape.setFillColor(color);
        shape.setOrigin(radius, radius); 
        shape.setPosition(position + sf::Vector2f(OFFSET_X, OFFSET_Y)); // Apply offset
        shape.setOutlineThickness(2);
        shape.setOutlineColor(sf::Color::Black);
    }

    void update(float deltaTime) {
        sf::Vector2f newPosition = shape.getPosition() + velocity * deltaTime;

        if (newPosition.x - BallRadius < TableBorder + OFFSET_X || newPosition.x + BallRadius > WindowWidth - TableBorder + OFFSET_X) {
            velocity.x = -velocity.x;
        }
        if (newPosition.y - BallRadius < TableBorder + OFFSET_Y || newPosition.y + BallRadius > WindowHeight - TableBorder + OFFSET_Y) {
            velocity.y = -velocity.y;
        }

        float friction = 0.99f; 
        velocity *= std::pow(friction, deltaTime * 120); 

        shape.setPosition(shape.getPosition() + velocity * deltaTime);

        if (std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y) < MinVelocity) {
            velocity = sf::Vector2f(0.0f, 0.0f);
        }
    }

    void applyForce(sf::Vector2f force) {
        velocity += force; 
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(shape);

        if (isStriped) {
            // Create a small white circle in the center for the stripe
            sf::CircleShape centerCircle(BallRadius / 2); // Diameter smaller than the ball's size
            centerCircle.setFillColor(sf::Color::White);
            
            // Center the circle at the middle of the ball
            centerCircle.setPosition(shape.getPosition().x, shape.getPosition().y); // No need for offset
            centerCircle.setOrigin(centerCircle.getRadius(), centerCircle.getRadius()); // Origin at center

            window.draw(centerCircle);
        }
    }

    sf::Vector2f getPosition() const {
        return shape.getPosition();
    }

    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }

    sf::Vector2f getVelocity() const {
        return velocity;
    }

    void setVelocity(const sf::Vector2f& newVelocity) {
        velocity = newVelocity;
    }

    void respawn() {
        shape.setPosition(initialPosition + sf::Vector2f(OFFSET_X, OFFSET_Y)); // Apply offset
        velocity = sf::Vector2f(0.0f, 0.0f); 
    }
};