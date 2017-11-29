#ifndef BRICK_H
#define BRICK_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

constexpr float blockWidth{60.f}, blockHeight{20.f};
constexpr int countBlocksX{11}, countBlocksY{4};

class Brick
{
public:
    Brick(float, float);
    ~Brick();

    sf::RectangleShape shape;

    bool isDestroyed{false};

    float x();
    float y();
    float left();
    float right();
    float top();
    float bottom();
};

#endif // BRICK_H
