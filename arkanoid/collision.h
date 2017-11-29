#ifndef COLLISION_H
#define COLLISION_H

#include "ball.h"
#include "paddle.h"
#include "brick.h"

template<class T1, class T2> bool isIntersecting(T1&,T2&);
void testCollision(Paddle&, Ball&);
void testCollision(Brick&, Ball&);

#endif // COLLISION_H
