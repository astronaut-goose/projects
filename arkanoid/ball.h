#ifndef BALL_H
#define BALL_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

constexpr float ballRadius{10.f}, ballVelocity{8.f};
constexpr int windowWidth{800}, windowHeight{600}; // naprawd, zrób to jako globalną

class Ball
{
public:
    // Ball constructor prototype
    Ball(float, float);
    ~Ball();

    // CircleShape is an SFML class that defines a renderable circle
    sf::CircleShape shape;
    sf::Vector2f velocityBall{-ballVelocity, -ballVelocity};
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
