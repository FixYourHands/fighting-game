
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include "Animation.h"



struct Circle
{
    float radius;

    float xpos;
    float ypos;

    float xspeed;
    float yspeed;

    int red;
    int green;
    int blue;

    bool isMovingLeft;
    bool isMovingRight;
    bool isMovingDown;
    bool isMovingUp;
    Circle(float radius, float xpos, float ypos)
        :radius(radius),xpos(xpos),ypos(ypos)
        ,isMovingLeft(1),isMovingRight(1)
        ,isMovingUp(1),isMovingDown(1)
        ,red(255),green(255),blue(255)
    {
        xspeed = 2.0f;
        yspeed = 2.0f;
    }

    void moveRight()
    {
        xpos += xspeed;
    }

    void moveLeft()
    {
        xpos -= xspeed;
    }

    void moveUp()
    {
        ypos -= xspeed;
    }

    void moveDown()
    {
        ypos += xspeed;
    }
};
struct Square
{
    sf::RectangleShape square;
    float length;

    float xpos;
    float ypos;

    float xspeed;
    float yspeed;

    int red;
    int green;
    int blue;

    bool isMovingLeft;
    bool isMovingRight;
    bool isMovingDown;
    bool isMovingUp;
    Square(float length, float xpos, float ypos)
        :length(length), xpos(xpos), ypos(ypos)
        , isMovingLeft(1), isMovingRight(1)
        , isMovingUp(1), isMovingDown(1)
        , red(255), green(255), blue(255)
    {
        //way to include vector2f without screen glitches
        sf::RectangleShape data(sf::Vector2f(length, length+25.0f));
        xspeed = 2.0f;
        yspeed = 2.0f;
        square = data;
        square.setFillColor(sf::Color(0,green,blue));
    }

    void moveRight()
    {
        xpos += xspeed;
    }

    void moveLeft()
    {
        xpos -= xspeed;
    }

    void moveUp()
    {
        ypos -= xspeed;
    }

    void moveDown()
    {
        ypos += xspeed;
    }
};

template <typename T>
void refresh(sf::RenderWindow& window, T& shape)
{
    window.clear();
    window.draw(shape);
    window.display();
}

bool inBounds(const sf::VideoMode& window, const Circle& shape)
{
    if ((shape.xpos <= window.width) || (shape.xpos >= 0))
    {
        if ((shape.ypos <= window.height) || (shape.ypos >= 0))
        {
            return true;
        }
    }
    return false;
}

int main()
{
    srand(time(0));
    float chance = (rand() % 10)/10.0f;
    //window settings
    constexpr  unsigned int windowWidth = 1280;
    constexpr unsigned int windowHeight = 720;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!");
    window.setFramerateLimit(60);
    sf::Event event;
    
    
  
    
    //setup player
    Square square1(100, 0, 0);
    auto& player1 = square1.square; //shorter name
    player1.setOrigin(25.0f, 25.0f);
    sf::Texture playerTexture;

    
    player1.setTexture(&playerTexture);
    sf::IntRect rectSourceSprite(0, 0, 80, 152);
    sf::Sprite sprite(playerTexture,rectSourceSprite);

    sf::Clock clock;

    
    


    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                std::cout << "New window size: " << event.size.width << ' ' << event.size.height << '\n';
            case sf::Event::TextEntered:
                std::cout << (char)event.text.unicode << '\n';
                break;
            }
        }
        if (clock.getElapsedTime().asSeconds() > 1.0f)
        {
            if (rectSourceSprite.left == 800)
            {
                rectSourceSprite.left = 0;
            }
            else
            {
                rectSourceSprite.left += 100;
            }
            sprite.setTextureRect(rectSourceSprite);
            clock.restart();
        }
        
        //move shape with keyboard
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            playerTexture.loadFromFile("Textures/DeeJayLeft.png");
            player1.setTexture(&playerTexture);
            player1.move(-1.0f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            playerTexture.loadFromFile("Textures/DeeJayRight.png");
            player1.setTexture(&playerTexture);
            player1.move(1.0f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            player1.move(0.0f, -1.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            player1.move(0.0f, 1.0f);
        }

        //move shape to mouse position on click
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            auto mousePos = sf::Mouse::getPosition(window);
            player1.setPosition(static_cast<sf::Vector2f>(mousePos));
        }
        window.clear(); // clear old frame
        window.draw(sprite);
        //Draw your game
       // refresh(window, square1.square);
        window.display();
    }
   
    return 0;
}
