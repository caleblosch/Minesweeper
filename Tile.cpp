//
// Created by caleb on 11/18/2022.
//

#include "Tile.h"

Tile::Tile() {
    isUncovered = false;
    xCoord = 0;
    yCoord = 0;
    mine = false;
    oneMine = false;
    twoMine = false;
    threeMine = false;
    fourMine = false;
    fiveMine = false;
    sixMine = false;
    sevenMine = false;
    eightMine = false;
    noMines = false;
    isFlagged = false;
    fileName = "tile_hidden";
    mineSprite = sf::Sprite(TextureManager::GetTexture("mine"));
}

void Tile::DrawSprite(sf::RenderWindow &window) {
    tileSprite = sf::Sprite(TextureManager::GetTexture(fileName));
    tileSprite.setPosition(xCoord * 32,yCoord * 32);
    window.draw(tileSprite);
    if (this->Flagged()) {
        tileIcon = sf::Sprite(TextureManager::GetTexture("flag"));
        tileIcon.setPosition(xCoord * 32, yCoord * 32);
        window.draw(tileIcon);
    }
    if (this->isFlipped()) {
        if (this->isMine()) {
            tileIcon = sf::Sprite(TextureManager::GetTexture("mine"));
            tileIcon.setPosition(xCoord * 32, yCoord * 32);
            window.draw(tileIcon);
        } else {
            if (oneMine) {
                tileIcon = sf::Sprite(TextureManager::GetTexture("number_1"));
                tileIcon.setPosition(xCoord * 32, yCoord * 32);
                window.draw(tileIcon);
            } else if (twoMine) {
                tileIcon = sf::Sprite(TextureManager::GetTexture("number_2"));
                tileIcon.setPosition(xCoord * 32, yCoord * 32);
                window.draw(tileIcon);
            } else if (threeMine) {
                tileIcon = sf::Sprite(TextureManager::GetTexture("number_3"));
                tileIcon.setPosition(xCoord * 32, yCoord * 32);
                window.draw(tileIcon);
            } else if (fourMine) {
                tileIcon = sf::Sprite(TextureManager::GetTexture("number_4"));
                tileIcon.setPosition(xCoord * 32, yCoord * 32);
                window.draw(tileIcon);
            } else if (fiveMine) {
                tileIcon = sf::Sprite(TextureManager::GetTexture("number_5"));
                tileIcon.setPosition(xCoord * 32, yCoord * 32);
                window.draw(tileIcon);
            } else if (sixMine) {
                tileIcon = sf::Sprite(TextureManager::GetTexture("number_6"));
                tileIcon.setPosition(xCoord * 32, yCoord * 32);
                window.draw(tileIcon);
            } else if (sevenMine) {
                tileIcon = sf::Sprite(TextureManager::GetTexture("number_7"));
                tileIcon.setPosition(xCoord * 32, yCoord * 32);
                window.draw(tileIcon);
            } else if (eightMine) {
                tileIcon = sf::Sprite(TextureManager::GetTexture("number_8"));
                tileIcon.setPosition(xCoord * 32, yCoord * 32);
                window.draw(tileIcon);
            }
        }
    }
}

void Tile::setPosition(int x, int y) {
    xCoord = x;
    yCoord = y;
}

void Tile::flipSprite() {
    isUncovered = true;
    fileName = "tile_revealed";
    if(!mine) {
        if (noMines) {
            for (auto &neighborTile: neighborTiles) {
                if ((!neighborTile->isMine()) && (!neighborTile->isFlipped()) && (!neighborTile->Flagged())) {
                    neighborTile->flipSprite();
                }
            }
        }
    }
}

bool Tile::isFlipped() const {
    return isUncovered;
}

void Tile::setMine() {
    mine = true;
}

bool Tile::isMine() const {
    return mine;
}

void Tile::setNeighbors(unordered_map<string, Tile> &gameMap, int x, int y) {
    vector<unordered_map<string,Tile>::iterator> tempVec;
    auto tTile = gameMap.find("(" + to_string(x) + ", " + to_string(y - 1) + ")");
    tempVec.push_back(tTile);
    auto tRTile = gameMap.find("(" + to_string(x + 1) + ", " + to_string(y - 1) + ")");
    tempVec.push_back(tRTile);
    auto rTile = gameMap.find("(" + to_string(x + 1) + ", " + to_string(y) + ")");
    tempVec.push_back(rTile);
    auto bRTile = gameMap.find("(" + to_string(x + 1) + ", " + to_string(y + 1) + ")");
    tempVec.push_back(bRTile);
    auto bTile = gameMap.find("(" + to_string(x) + ", " + to_string(y + 1) + ")");
    tempVec.push_back(bTile);
    auto bLTile  = gameMap.find("(" + to_string(x - 1) + ", " + to_string(y + 1) + ")");
    tempVec.push_back(bLTile);
    auto lTile = gameMap.find("(" + to_string(x - 1) + ", " + to_string(y) + ")");
    tempVec.push_back(lTile);
    auto tLTile  = gameMap.find("(" + to_string(x - 1) + ", " + to_string(y - 1) + ")");
    tempVec.push_back(tLTile);
    for (auto & i : tempVec) {
        if (i != gameMap.end()) {
            neighborTiles.push_back(&i->second);
        }
    }
}

int Tile::GetXCoord() const {
    return xCoord;
}

int Tile::GetYCoord() const {
    return yCoord;
}

void Tile::setMineNeighborCount() {
    int count = 0;
    for (auto & neighborTile : neighborTiles) {
        if (neighborTile->isMine())
            count++;
    }
    switch (count) {
        case(1):
            oneMine = true;
            break;
        case(2):
            twoMine = true;
            break;
        case(3):
            threeMine = true;
            break;
        case(4):
            fourMine = true;
            break;
        case(5):
            fiveMine = true;
            break;
        case(6):
            sixMine = true;
            break;
        case(7):
            sevenMine = true;
            break;
        case(8):
            eightMine = true;
            break;
        case(0):
            noMines = true;
            break;
    }
}

void Tile::debugReveal(sf::RenderWindow &window) {
    if (this->isMine()) {
        mineSprite.setPosition(xCoord * 32, yCoord * 32);
        window.draw(mineSprite);
    }
}

void Tile::flag() {
    if (!isUncovered) {
        isFlagged = !isFlagged;
    }
}

void Tile::endFlag() {
    isFlagged = true;
}

bool Tile::Flagged() {
    return isFlagged;
}