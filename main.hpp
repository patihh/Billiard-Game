#ifndef BILLIARD_HPP
#define BILLIARD_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

const float TABLE_WIDTH = 1100.0f;
const float TABLE_HEIGHT = 600.0f;
const float BALL_RADIUS = 18.0f;

// === Deklarasi Kelas Ball ===
class Ball {
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    bool isStriped;  

public:
    Ball(float radius, const sf::Color& color, bool isStriped, const sf::Vector2f& position, const sf::Vector2f& initialVelocity);


    void update(float deltaTime, const sf::FloatRect& tableBounds);
    void draw(sf::RenderWindow& window) const;

    sf::Vector2f getPosition() const;
    void setVelocity(const sf::Vector2f& vel);
    bool getIsStriped() const;
};

// === Deklarasi Kelas Table ===
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

// === Deklarasi Kelas CueStick ===
class CueStick {
private:
    sf::RectangleShape stick;

public:
    CueStick(float length, float thickness, const sf::Vector2f& position);
    void update(const sf::Vector2i& mousePos);
    void draw(sf::RenderWindow& window) const;
};

// === Deklarasi Kelas Game ===
class Game {
private:
    Table table;
    Ball whiteBall;
    std::vector<Ball> balls;
    CueStick cueStick;

    void setupBalls();

public:
    Game();
    void update(float deltaTime, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

#endif