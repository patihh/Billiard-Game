#ifndef GAME_HPP
#define GAME_HPP

#include "../Ball/Ball.hpp"
#include "../Table/Table.hpp"
#include "../CueStick/CueStick.hpp"
#include <vector>

const float TABLE_WIDTH = 1100.0f;
const float TABLE_HEIGHT = 600.0f;
const float BALL_RADIUS = 18.0f;

class Game {
private:
    Table table;
    Ball whiteBall;
    std::vector<Ball> balls;
    CueStick cueStick;

    void handleCollisions();
    bool checkCollision(Ball& ball1, Ball& ball2);
    void checkPockets();
    void setupBalls();

public:
    Game();
    void update(float deltaTime, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    bool checkPockets(Ball& ball);
};

#endif