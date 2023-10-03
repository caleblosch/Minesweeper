//
// Created by caleb on 11/18/2022.
//

#include "NumClass.h"

NumClass::NumClass() {
    numTexture.loadFromFile("images/number_1.png");
    numSprite.setTexture(numTexture);
    numSprite.scale(2,2);
}

NumClass::NumClass(string filename) {
    numTexture.loadFromFile(filename);
    numSprite.setTexture(numTexture);
    numSprite.scale(2,2);
}

void NumClass::setPosition(float xCoor, float yCoor) {
    numSprite.setPosition(xCoor, yCoor);
}

void NumClass::draw(sf::RenderWindow &window) {
    window.draw(numSprite);
}