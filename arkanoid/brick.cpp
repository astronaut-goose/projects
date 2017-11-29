#include "brick.h"

Brick::Brick(float mX, float mY)
{
    // Apply position, radius, color and origin to the RectangleShape object
    shape.setPosition(mX, mY);
    shape.setSize({blockWidth, blockHeight});
    shape.setFillColor(sf::Color::Yellow);
    shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
};

Brick::~Brick(){};

float Brick::x()         { return shape.getPosition().x; }
float Brick::y()         { return shape.getPosition().y; }
float Brick::left()      { return x() - shape.getSize().x / 2.f; }  // subtract center of x and the balls radius to get the left edge of the ball
float Brick::right()     { return x() + shape.getSize().x / 2.f; }
float Brick::top()       { return y() - shape.getSize().y / 2.f; }
float Brick::bottom()    { return y() + shape.getSize().y / 2.f; }
