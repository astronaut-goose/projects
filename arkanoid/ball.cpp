#include "ball.h"

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

void Ball::update()
{
    shape.move(velocity);

    // Keep the ball inside the screen
    if(left() < 0) velocity.x = ballVelocity;

    else if(right() > myConstants::windowWidth) velocity.x = -ballVelocity;

    if(top() < 0) velocity.y = ballVelocity;

    else if(bottom() > myConstants::windowHeight) velocity.y = -ballVelocity;
}
float Ball::x()         { return shape.getPosition().x; }
float Ball::y()         { return shape.getPosition().y; }
float Ball::left()      { return x() - shape.getRadius(); }  // subtract center of x and the balls radius to get the left edge of the ball
float Ball::right()     { return x() + shape.getRadius(); }
float Ball::top()       { return y() - shape.getRadius(); }
float Ball::bottom()    { return y() + shape.getRadius(); }
