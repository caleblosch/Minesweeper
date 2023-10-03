//
// Created by caleb on 11/24/2022.
//

#pragma
#include "Tile.h"

class Face: public Tile {
    string faceFile = "face_happy";
public:
    void DrawFace(sf::RenderWindow &window) {
        tileSprite = sf::Sprite(TextureManager::GetTexture(faceFile));
        tileSprite.setPosition(xCoord, yCoord);
        window.draw(tileSprite);
    }
    void setPosition(int boardWidth, int boardHeight) override {
        if (boardWidth % 2 == 0) { // if the number of columns is an even number, this sets there positions in a way different to if it were an odd number
            xCoord = ((boardWidth / 2) - 1) * 32;
            yCoord = boardHeight * 32;
        } else { // if the number of columns is an odd number, it sets all the buttons at the bottom in a different way
            xCoord = (32 * boardWidth) / 2 - 32;
            yCoord = boardHeight * 32;
        }
    }
    string getFilename() {
        return faceFile;
    }
    void setFace(string filename) {
        faceFile = filename;
    }
 };
