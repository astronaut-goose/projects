#ifndef BALL_H
#define BALL_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "constants.h"

constexpr float ballRadius{10.f}, ballVelocity{8.f};

class Ball
{
public:
    // Ball constructor prototype
    Ball(float, float);
    ~Ball();

    // CircleShape is an SFML class that defines a renderable circle
    sf::CircleShape shape;
    // 2D vector that stores paddle's velocity
    sf::Vector2f velocity{-ballVelocity, -ballVelocity};
    // Updating the ball: move its shape by the current velocity
    void update();

    // "Property" methods to easily get commonly used values
    float x();
    float y();
    float left();
    float right();
    float top();
    float bottom();
};

#endif // BALL_H
