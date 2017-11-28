#include "collision.h"

template<class T1, class T2> bool isIntersecting(T1& mA,T2& mB)
{
    return mA.right() >= mB.left() && mA.left() <= mB.right()
           && mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

void testCollision(Paddle& mPaddle, Ball& mBall)
{
    if(!isIntersecting(mPaddle, mBall)) return;

    mBall.velocityBall.y = -ballVelocity;

    if(mBall.x() < mPaddle.x()) mBall.velocityBall.x = -ballVelocity;
    else mBall.velocityBall.x = ballVelocity;
}
