#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Paddle
{
public:
    // Paddle constructor prototype
    Paddle(float, float);
    ~Paddle();

    // RectangleShape is an SFML class that defines a renderable circle
    sf::RectangleShape shape;

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

#endif // PADDLE_H
