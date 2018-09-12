#ifndef TZFE_GAME_TWOFOURZEREIGHT_HPP_
#define TZFE_GAME_TWOFOURZEREIGHT_HPP_

//============================================================================
// Name        : twozerofoureight.hpp
// Author      : Steve Richards
// Created on  : 06/09/18.
// Version     :
// Copyright   : Your copyright notice
// Description : 2048 Game twozerofoureight object definitions
//============================================================================


#include "transition.hpp"

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

namespace tzfe_engine {

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
        int mScore, mMaxTile, mNumEmpty;   // value to store score and state related details
        int mTiles[GRID_CNT];              // the array to hold the game board values.
        std::vector<tzfe_engine::Transition> mTransitions; // vector to hold a sequence of transitions

        void createNewTransitions() { mTransitions = std::vector<tzfe_engine::Transition>(); }
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
            mScore = 0;
            mMaxTile = 0;
            mNumEmpty = GRID_CNT;  
            createNewTransitions();
            for (int i = 0; i < GRID_CNT; i++) { mTiles[i] = BLANK;}
            addNewTile();
            addNewTile();
        }

        std::vector<Transition>& getTransitions() { return mTransitions; }
        int getMaxTile() { return mMaxTile; }    
        int getValue(int i) { return (mTiles[i]); }
        int getScore() { return mScore; }

        void rePlot();
        bool hasMovesRemaining();
        bool gameWon() { return mMaxTile >= TARGET; }
        bool actionMove(Moves move);
        std::string toString();
    };

}  // end namespace tzfe_engine


#endif  // TZFE_GAME_TWOFOURZEREIGHT_HPP_
