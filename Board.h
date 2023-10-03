//
// Created by caleb on 11/21/2022.
//

#pragma
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "Random.h"
using std::string;

class Board {
    int width;
    int height;
    vector<vector<int>> gameBoard;
    int numMines;
public:
    void SetGameBoard(int widthOfBoard, int heightOfBoard, int numberOfMines) {
        width = widthOfBoard;
        height = heightOfBoard;
        int minesInPlay = numberOfMines;
        numMines = 0;
        gameBoard.resize(height, vector<int>(width));
        for (int h = 0; h < height; h++) {
            for (int w = 0; w < width; w++) {
                gameBoard[h][w] = 0;
            }
        }
        while (numMines < minesInPlay) {
            int randY = Random::Int(0,height - 1);
            int randX = Random::Int(0,width - 1);
            if (gameBoard[randY][randX] != 1) {
                gameBoard[randY][randX] = 1;
                numMines++;
            }
        }
    }
    void SetPrefabBoard(string filename, int widthOfBoard, int heightOfBoard) {
        ifstream gameFile;
        string path = "boards/" + filename + ".brd";
        gameFile.open(path);
        if (gameFile.is_open()) {
            string rowOfBoard;
            width = widthOfBoard;
            height = heightOfBoard;
            numMines = 0;
            gameBoard.resize(height, vector<int>(width));
            for (int h = 0; h < height; h++) {
                getline(gameFile, rowOfBoard);
                vector<char> row (rowOfBoard.begin(), rowOfBoard.end());
                for (int w = 0; w < width; w++) {
                    int tileValue = row.at(w) - 48;
                    gameBoard[h][w] = tileValue;
                    if (tileValue == 1) {
                        numMines++;
                    }
                }
            }
        }
    }
    vector<vector<int>> getGameBoard() {
        return gameBoard;
    }
    int getMines() {
        return numMines;
    }
};
