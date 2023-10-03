#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "NumClass.h"
using namespace std;

int mai() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");

    NumClass num1("images/number_1.png");
    NumClass num2("images/number_2.png");
    sf::Texture num3Texture;
    num3Texture.loadFromFile("images/number_3.png");
    sf::Sprite num3;
    num3.setTexture(num3Texture);
    num3.scale(2,2);
    sf::Texture num4Texture;
    num4Texture.loadFromFile("images/number_4.png");
    sf::Sprite num4;
    num4.setTexture(num4Texture);
    num4.scale(2,2);
    sf::Texture num5Texture;
    num5Texture.loadFromFile("images/number_5.png");
    sf::Sprite num5;
    num5.setTexture(num5Texture);
    num5.scale(2,2);



    while (window.isOpen()) {
        //cout << "The window is open!" << endl;

        sf::Event event;
        while (window.pollEvent(event))
        {
            //cout << "Hello World in 2D!" << endl;
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2 coordinates = sf::Mouse::getPosition(window);
                cout << "(X: " << coordinates.x << ", ";
                cout << "Y: " << coordinates.y << ")" << endl;
            }
            if (event.type == sf::Event::KeyPressed) {
                window.close();
            }
         }

        window.clear();
        num1.setPosition(100, 100);
        num1.draw(window);
        num2.setPosition(200, 100);
        num2.draw(window);
        num3.setPosition(300, 100);
        window.draw(num3);


        window.display();
    }

    return 0;
}