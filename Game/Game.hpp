#ifndef GAME_HPP
#define GAME_HPP

#include "../Ball/Ball.hpp"
#include "../Table/Table.hpp"
#include "../CueStick/CueStick.hpp"
#include <vector>

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