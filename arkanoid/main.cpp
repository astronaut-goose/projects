#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "constants.h"

#include "ball.h"
#include "paddle.h"
#include "brick.h"
#include "collision.h"

int main()
{
    // Create instance of Ball (at the center of the window)
    Ball ball{myConstants::windowWidth / 2, myConstants::windowHeight / 2};

    // Create instance of Paddle
    Paddle paddle{myConstants::windowWidth / 2, myConstants::windowHeight - 50};

    // Create instances (40) of Bricks
    std::vector<Brick> bricks;

    for (size_t i = 0; i < countBlocksX; i++){
        for (size_t y = 0; y < countBlocksY; y++) {
            bricks.emplace_back((i + 1) * (blockWidth + 3) + 22,
                                (y + 2) * (blockHeight + 3));
        }
    }


    // Create game window
    sf::RenderWindow window{{myConstants::windowWidth, myConstants::windowHeight}, "Arkanoid v1"};
    window.setFramerateLimit(60);

    // Game loop
    while(true){

        // Clear the window
        window.clear(sf::Color::Black);

        // If escape button is pressed, break out of loop
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) break;

        // Every loop iteration, update the ball
        ball.update();
        // Every loop iteration, update the paddle
        paddle.update();

        // Testing collision every loop iteration
        testCollision(paddle, ball);

        // Testing collision with all the bricks every loop iteration
        for(auto& brick : bricks) testCollision(brick, ball);

        /* And destroying every touched brick
         *
         * bricks.erase (start_iterator, end_iterator); <- deletes everyting inbetween 2 iterators
         * remove_if (begin(bricks), end(bricks),
         *
         *
        */

        bricks.erase(remove_if(begin(bricks), end(bricks),
            [](const Brick& mBrick){return mBrick.isDestroyed; }),
            end(bricks));

        // Render Ball
        window.draw(ball.shape);
        // Render Paddle
        window.draw(paddle.shape);
        // Render bricks -- foreach loop
        for(auto& brick : bricks) window.draw(brick.shape);

        // Show window contents
        window.display();
    }

    return 0;
}
