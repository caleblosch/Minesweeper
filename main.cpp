//
// Created by caleb on 11/18/2022.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Tile.h"
#include "TextureManager.h"
#include "Board.h"
#include "Face.h"
using namespace std;

void setTileMap(unordered_map<string, Tile> &tMap, vector<vector<int>> &tVec, int boardWidth, int boardHeight);

int main() {
    int numRows;
    int numColumns;
    int numMines;
    int tilesRevealed; // keeps track of how many files have been flipped to test for the win condition
    int tilesFlagged = 0; // keeps track of how many files are flagged to change the mine counter
    bool debugging = false; // keeps track of the state of the game and determines if the mines need ot be drawn in debugger mode
    bool gameOver = false; // keeps track of the state of the program and determines if the user has either clicked a mine or won the game
    unordered_map<string, Tile> tilesMap; // initializes an unordered map that will be used to store the instances of the Tile class with its coordinates in board stored as its key
    vector<vector<int>> gameBoardVec; // initializes the game board 2D vector with ones and zeros that defines how the mines are placed

    // Loading in the game board information from the config file
    ifstream config("boards/config.cfg"); // opens the config files and loads all the values
    if(config.is_open()) {
        config >> numColumns;
        config >> numRows;
        config >> numMines;
    } else { // in case the config file fails to open, sets some default values so the game can still be played
        numColumns = 25;
        numRows = 16;
        numMines = 50;
        cout << "The file failed to open!" << endl;
    }

    Board gameBoard;
    gameBoard.SetGameBoard(numColumns, numRows, numMines); // initializes the game board vector with the set number of columns and row with the set number of mines in random spots

    Face gameState;
    gameState.setPosition(numColumns, numRows); // initializes the face sprite at the bottom of the page that communicates the state of the game

    gameBoardVec = gameBoard.getGameBoard(); //
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numColumns; c++) {
            cout << "Game Board [" << r + 1 << "][" << c + 1 << "]: " << gameBoardVec[r][c] << endl;
        }
    }

    // creating all the sprites for the buttons at the bottom of the game board
    sf::Sprite test1(TextureManager::GetTexture("test_1"));
    sf::Sprite test2(TextureManager::GetTexture("test_2"));
    sf::Sprite test3(TextureManager::GetTexture("test_3"));
    sf::Sprite debug(TextureManager::GetTexture("debug"));
    sf::Sprite tempFace(TextureManager::GetTexture(gameState.getFilename())); // initializes a sprite that will have the same bounds as the face object that communicates the game state
    tempFace.setPosition(gameState.GetXCoord(), gameState.GetYCoord()); // sets it to same position as the face object


    // Displaying the game window, its size is set by the number of desired rows * the amount of pixels in a square
    sf::RenderWindow window(sf::VideoMode(32*numColumns, 32*numRows + 100), "Minesweeper");

    // while the window is open, it allows the program to continue executing but once it is closed, the program will halt
    while (window.isOpen()) {
        sf::Event event{};
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                // sets up the values that will be needed for either a right or left click
                sf::Vector2 coordinates = sf::Mouse::getPosition(window);
                int xCoord = coordinates.x / 32; // gives the row of tile
                int yCoord = coordinates.y / 32; // gives the column of the tile
                auto finder = tilesMap.find("(" + to_string(xCoord) + ", " + to_string(yCoord) + ")"); // looks through the map to see if the user clicked a tile and which one
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // this is how the user flips tiles
                    if (!gameOver) { // checks to see if the game is over prior to allowing the user to flip a mine
                        // Finding where the mouse has clicked and converting it into the row and column location of the tile
                        if (finder != tilesMap.end()) { // if the user did click valid tile, it will flip the tile, displaying either a blank tile, a number, and if it's a mine, it will end the game
                            if (!finder->second.Flagged()) {
                                finder->second.flipSprite();
                                if (finder->second.isMine()) {
                                    cout << "Game Over!" << endl;
                                    gameOver = true; // sets the state of the game to game over
                                    debugging = false; // ends the debugging mode as all the mines get revealed
                                    gameState.setFace("face_lose");
                                    auto iter = tilesMap.begin();
                                    for (; iter != tilesMap.end(); iter++) { // goes through the tile map and flips all the mines if the game is over
                                        if (iter->second.isMine()) {
                                            iter->second.flipSprite();
                                        }
                                    }
                                }
                            }
                        }
                        if (debug.getGlobalBounds().contains(coordinates.x, coordinates.y)) {
                            debugging = !debugging; // if the debugger button is clicked, it sets debugging mode to its opposite value as it can be turned on and off many times during the running of the program
                        }
                    }
                    // checks to see if the mouse was inside any of the buttons when the user did a left click
                    // this is outside the if (!gameOver) statement because these can be clicked whenever the program is running
                    if (test1.getGlobalBounds().contains(coordinates.x, coordinates.y)) {
                        gameBoard.SetPrefabBoard("testboard1", numColumns, numRows);
                        gameBoardVec = gameBoard.getGameBoard();
                        setTileMap(tilesMap, gameBoardVec, numColumns, numRows);
                        gameState.setFace("face_happy");
                        tilesFlagged = 0;
                        gameOver = false;
                    }
                    if (test2.getGlobalBounds().contains(coordinates.x, coordinates.y)) {
                        gameBoard.SetPrefabBoard("testboard2", numColumns, numRows);
                        gameBoardVec = gameBoard.getGameBoard();
                        setTileMap(tilesMap, gameBoardVec, numColumns, numRows);
                        gameState.setFace("face_happy");
                        tilesFlagged = 0;
                        gameOver = false;
                    }
                    if (test3.getGlobalBounds().contains(coordinates.x, coordinates.y)) {
                        gameBoard.SetPrefabBoard("testboard3", numColumns, numRows);
                        gameBoardVec = gameBoard.getGameBoard();
                        setTileMap(tilesMap, gameBoardVec, numColumns, numRows);
                        gameState.setFace("face_happy");
                        tilesFlagged = 0;
                        gameOver = false;
                    }
                    if (tempFace.getGlobalBounds().contains(coordinates.x, coordinates.y)) {
                        gameBoard.SetGameBoard(numColumns, numRows, numMines);
                        gameBoardVec = gameBoard.getGameBoard();
                        setTileMap(tilesMap, gameBoardVec, numColumns, numRows);
                        gameState.setFace("face_happy");
                        tilesFlagged = 0;
                        gameOver = false;
                    }
                }
                if (!gameOver) {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) { // if the user does a right click, it determines whether it was a valid click to place or remove a placed mine and does it
                        if (finder != tilesMap.end())
                            if (finder->second.Flagged() && !finder->second.isFlipped()) {
                                tilesFlagged++;
                            } else if (!finder->second.Flagged() && !finder->second.isFlipped()) {
                                tilesFlagged--;
                            }
                        finder->second.flag();
                    }
                }
            }
        }

        window.clear();

        gameState.DrawFace(window);

        // does the math to determine which part of the part of the digits texture file is needed to be displayed
        int mineCounter = gameBoard.getMines() + tilesFlagged;
        int hP = abs(mineCounter / 100); // hundreds place digit
        int tP = abs((mineCounter % 100) / 10); // tens place digit
        int oP = abs(((mineCounter % 100) % 10)); // ones place digit
        if (mineCounter < 0) { // determines if the negative sign needs to be drawn (in the case of more mines the flags)
            sf::Sprite negativeSign(TextureManager::GetTexture("digits", 10));
            negativeSign.setPosition(0,32*numRows);
            window.draw(negativeSign);
        }
        sf::Sprite firstDigitSprite(TextureManager::GetTexture("digits", hP));
        firstDigitSprite.setPosition(22,32*numRows);
        window.draw(firstDigitSprite);
        sf::Sprite secondDigitSprite(TextureManager::GetTexture("digits", tP));
        secondDigitSprite.setPosition(43,32*numRows);
        window.draw(secondDigitSprite);
        sf::Sprite thirdDigitSprite(TextureManager::GetTexture("digits", oP));
        thirdDigitSprite.setPosition(64,32*numRows);
        window.draw(thirdDigitSprite);

        // if else statements to determine how to set the position of the buttons at the bottom
        if (numColumns % 2 == 0) { // if the number of columns is an even number, this sets there positions in a way different to if it were an odd number
            debug.setPosition(((numColumns / 2) + 3) * 32, numRows * 32);
            window.draw(debug);
            test1.setPosition(((numColumns / 2) + 5) * 32, numRows * 32);
            window.draw(test1);
            test2.setPosition(((numColumns / 2) + 7) * 32, numRows * 32);
            window.draw(test2);
            test3.setPosition(((numColumns / 2) + 9) * 32, numRows * 32);
            window.draw(test3);
        } else { // if the number of columns is an odd number, it sets all the buttons at the bottom in a different way
            debug.setPosition((32 * numColumns) / 2 + (32 * 3), numRows * 32);
            window.draw(debug);
            test1.setPosition((32 * numColumns) / 2 + (32 * 5), numRows * 32);
            window.draw(test1);
            test2.setPosition((32 * numColumns) / 2 + (32 * 7), numRows * 32);
            window.draw(test2);
            test3.setPosition((32 * numColumns) / 2 + (32 * 9), numRows * 32);
            window.draw(test3);
        }

        // Places all the instances of the tile class into a map that can be later accessed to draw the tile sprites
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numColumns; j++) {
                Tile tile;
                tile.setPosition(j, i);
                string xCoor = to_string(j);
                string yCoor = to_string(i);
                string Coordinate = "(" + xCoor + ", " + yCoor + ")";
                if (gameBoardVec[i][j] == 1)
                    tile.setMine();
                tilesMap.emplace(Coordinate, tile);
            }
        }

        // iterates through the unordered map of the tiles and draws them to the display window
        auto iter = tilesMap.begin();
        for (; iter != tilesMap.end(); iter++){
            iter->second.setNeighbors(tilesMap, iter->second.GetXCoord(), iter->second.GetYCoord());
            iter->second.setMineNeighborCount();
            iter->second.DrawSprite(window);
        }

        // iterates through the map to determine how many tiles are flipped
        iter = tilesMap.begin();
        int tempFlips = 0;
        for (; iter != tilesMap.end(); iter++) {
            if (iter->second.isFlipped()) {
                tempFlips++;
            }
        }

        tilesRevealed = tempFlips;
        // if the number of flipped tiles is equal to total tiles mines total mines, the user has flipped all possible tiles and has won the game
        if ((numColumns * numRows) - gameBoard.getMines() == tilesRevealed) {
            gameState.setFace("face_win");
            tilesFlagged = -1 * gameBoard.getMines();
            gameOver = true;
            debugging = false;
            iter = tilesMap.begin();
            for (; iter != tilesMap.end(); iter++) {
                if (iter->second.isMine())
                    iter->second.endFlag();
            }
        }

        // if in debug mode, all tiles with mines will have their mines drawn on top of them.
        if (debugging) {
            iter = tilesMap.begin();
            for (; iter != tilesMap.end(); iter++)
                iter->second.debugReveal(window);
        }

        window.display();
    }


    // Clears out any stores textures before the program ends
    TextureManager::Clear();

    return 0;
}
// function to reset the tile map whenever the user resets the initial one or uses a test board
void setTileMap(unordered_map<string, Tile> &tMap, vector<vector<int>> &tVec, int boardWidth, int boardHeight) {
    tMap.clear();
    for (int i = 0; i < boardHeight; i++) {
        for (int j = 0; j < boardWidth; j++) {
            Tile tile;
            tile.setPosition(j, i);
            string Coordinate = "(" + to_string(j) + ", " + to_string(i) + ")";
            if (tVec[i][j] == 1)
                tile.setMine();
            tMap.emplace(Coordinate, tile);
        }
    }
}