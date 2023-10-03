//
// Created by caleb on 11/18/2022.
//

#pragma once
#include <SFML/Graphics.hpp>
using namespace std;

class NumClass {
    sf::Texture numTexture;
    sf::Sprite numSprite;
public:
    NumClass();
    NumClass(string filename);
    void setPosition(float xCoor, float yCoor);
    void draw(sf::RenderWindow &window);
};