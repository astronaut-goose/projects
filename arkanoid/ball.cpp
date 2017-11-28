#include "ball.h"

//constexpr float ballRadius{10.f}, ballVelocity{8.f};
//constexpr int windowWidth{800}, windowHeight{600}; // naprawd, zrób to jako globalną

// 2D vector that stores ball's velocity
//sf::Vector2f velocityBall{-ballVelocity, -ballVelocity};

// Ball constructor
// mX -> starting x coordinate
// mY -> starting y coordinate
Ball::Ball(float mX, float mY)
{
    // Apply position, radius, color and origin to the CircleShape object
    shape.setPosition(mX, mY);
    shape.setRadius(ballRadius);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(ballRadius, ballRadius);
};

Ball::~Ball(){};

//Ball.velocity{-ballVelocity, -ballVelocity};

void Ball::update()
{
    shape.move(velocityBall);

    // Keep the ball inside the screen
    if(left() < 0) velocityBall.x = ballVelocity;

    else if(right() > windowWidth) velocityBall.x = -ballVelocity;

    if(top() < 0) velocityBall.y = ballVelocity;

    else if(bottom() > windowHeight) velocityBall.y = -ballVelocity;
}
float Ball::x()         { return shape.getPosition().x; }
float Ball::y()         { return shape.getPosition().y; }
float Ball::left()      { return x() - shape.getRadius(); }  // subtract center of x and the balls radius to get the left edge of the ball
float Ball::right()     { return x() + shape.getRadius(); }
float Ball::top()       { return y() - shape.getRadius(); }
float Ball::bottom()    { return y() + shape.getRadius(); }
