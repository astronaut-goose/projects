#include "paddle.h"

constexpr float paddleWidth{60.f}, paddleHeight{20.f}, paddleVelocity{6.f};
constexpr int windowWidth{800}, windowHeight{600}; // napraw, zrób to jako globalną

// 2D vector that stores paddle's velocity
sf::Vector2f velocityPaddle;

// Paddle constructor
// mX -> starting x coordinate
// mY -> starting y coordinate
Paddle::Paddle(float mX, float mY)
{
    // Apply position, radius, color and origin to the CircleShape object
    shape.setPosition(mX, mY);
    shape.setSize({paddleWidth, paddleHeight});
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(paddleWidth / 2.f, paddleHeight / 2.f);
};

Paddle::~Paddle(){};

void Paddle::update()
{
    shape.move(velocityPaddle);

    // Keep the ball inside the screen
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)
        && left() > 0){
        velocityPaddle.x = -paddleVelocity;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)
        && right() < windowWidth){
        velocityPaddle.x = paddleVelocity;
    }
    else velocityPaddle.x = 0;

}
float Paddle::x()         { return shape.getPosition().x; }
float Paddle::y()         { return shape.getPosition().y; }
float Paddle::left()      { return x() - shape.getSize().x / 2.f; }  // subtract center of x and the balls radius to get the left edge of the ball
float Paddle::right()     { return x() + shape.getSize().x / 2.f; }
float Paddle::top()       { return y() - shape.getSize().y / 2.f; }
float Paddle::bottom()    { return y() + shape.getSize().y / 2.f; }
