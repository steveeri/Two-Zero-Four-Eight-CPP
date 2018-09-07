// Created by steve on 06/09/18.

#pragma once

#include "transition.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::cout;

/*
 * The below enumeration define allowed game board move types, and board size parameters
 */
enum Moves {LEFT, RIGHT, UP, DOWN};

/*
 * The below class defined the 2048 game engine class.
 */
class TwoZeroFourEight {

    static const int GRID_CNT = 16, GRID_SIZE = 4, ROW_CNT = 4, COL_CNT = 4, BLANK = 0, TARGET = 2048;

private:
    int score = 0, maxTile = 0;     // value to store score details
    int numEmpty = GRID_CNT;        // value to keep track of empty tiles
    int tiles[GRID_CNT];            // the array to hold the game board values.

    vector<Transition> transitions; // vector to hold a sequence of transitions

    void createNewTransitions() { transitions = vector<Transition>(); }
    bool addNewTile();
    bool slideTileRowOrColumn(int index1, int index2, int index3, int index4);
    bool compactTileRowOrColumn(int index1, int index2, int index3, int index4);
    bool slideLeft();
    bool slideRight();
    bool slideUp();
    bool slideDown();
    bool compactLeft();
    bool compactRight();
    bool compactUp();
    bool compactDown();
    bool actionMoveLeft();
    bool actionMoveRight();
    bool actionMoveUp();
    bool actionMoveDown();

public:
    TwoZeroFourEight() {
        this->createNewTransitions();
        for (int i = 0; i < GRID_CNT; i++) { this->tiles[i] = BLANK;}
        this->addNewTile();
        this->addNewTile();
    }

    vector<Transition> getTransitions() { return this->transitions; }
    int getMaxTile() { return this->maxTile; }
    int getValue(int i) { return (tiles[i]); }
    int getScore() { return score; }

    void rePlot();
    bool hasMovesRemaining();
    bool actionMove(Moves move);
    string toString();
};



