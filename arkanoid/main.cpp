#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "ball.h"
#include "paddle.h"
#include "collision.h"

constexpr int windowWidth{800}, windowHeight{600};

int main()
{
    // Create instance of Ball (at the center of the window)
    Ball ball{windowWidth / 2, windowHeight /2 };

    // Create instance of Paddle
    Paddle paddle{windowWidth / 2, windowHeight - 50};

    // Create game window
    sf::RenderWindow window{{windowWidth, windowHeight}, "Arkanoid v1"};
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

        // Render Ball
        window.draw(ball.shape);
        // Render Paddle
        window.draw(paddle.shape);

        // Show window contents
        window.display();
    }

    return 0;
}
