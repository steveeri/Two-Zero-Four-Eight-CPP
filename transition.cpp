//============================================================================
// Name        : transition.cpp
// Author      : Steve Richards
// Created on  : 06/09/18.
// Version     :
// Copyright   : Your copyright notice
// Description : 2048 Game Transition object implementation.
//============================================================================

#include "transition.hpp"

namespace tzfe_engine {

    /*
    * Transition effectively holds an instruction for a movement of tiles on the 2048 game board.
    * The collection of sequences of individual transitions describes all the tile movements that
    * may have occurred during a single game play.  They are recorded as different types, hence if
    * required different animation or treatments can be applied when updating the game board.
    *
    * Holding a collection "of collections of moves" can also be held to allow the game board to
    * be restored to a previous state allowing - hence undo actions can be achieved;
    */
    Transition::Transition(const actions action, int val, int newLocation, int oldLocation)
        : mType(action), mVal(val), mNewLocation(newLocation), mOldLocation(oldLocation) {
    }

    Transition::Transition(actions action, int val, int newLocation)
        : mType(action), mVal(val), mNewLocation(newLocation) {
        this->mOldLocation = -1;
    }

}  // end namespace tzfe_engine;

