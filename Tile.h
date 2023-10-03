//
// Created by caleb on 11/18/2022.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <iostream>
using namespace std;


class Tile {
    string fileName;
    bool isUncovered;
    bool mine;
    vector<Tile*> neighborTiles;
    bool oneMine;
    bool twoMine;
    bool threeMine;
    bool fourMine;
    bool fiveMine;
    bool sixMine;
    bool sevenMine;
    bool eightMine;
    bool noMines;
    bool isFlagged;
    sf::Sprite mineSprite;
    sf::Sprite numberSprite;
protected:
    int xCoord;
    int yCoord;
    sf::Sprite tileSprite;
    sf::Sprite tileIcon;
public:
    Tile();
    virtual void setPosition (int xCoor, int yCoor);
    void DrawSprite(sf::RenderWindow &window);
    void flipSprite();
    bool isFlipped() const;
    void setMine();
    bool isMine() const;
    int GetXCoord() const;
    int GetYCoord() const;
    void setNeighbors(unordered_map<string, Tile> &gameMap, int x, int y);
    void setMineNeighborCount();
    void debugReveal(sf::RenderWindow &window);
    void flag();
    void endFlag();
    bool Flagged();
};

