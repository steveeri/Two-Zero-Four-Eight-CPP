#ifndef TZFE_GAME_TRANSITION_HPP_
#define TZFE_GAME_TRANSITION_HPP_

//============================================================================
// Name        : transition.hpp
// Author      : Steve Richards
// Created on  : 06/09/18.
// Version     :
// Copyright   : Your copyright notice
// Description : 2048 Game Transition object definitions
//============================================================================

namespace tzfe_engine {

/*
 * The below enumeration define allowed transition action types.
 */
enum actions {
  ADD, CLEAR, SLIDE, COMPACT, REFRESH
};

/*
 * Transition effectively holds an instruction for a movement of tiles on the 2048 game board.
 * The collection of sequences of individual transitions describes all the tile movements that
 * may have occurred during a single game play.  They are recorded as different types, hence if
 * required different animation or treatments can be applied when updating the game board.
 *
 * Holding a collection "of collections of moves" can also be held to allow the game board to
 * be restored to a previous state allowing - hence undo actions can be achieved;
 */
class Transition {
public:
  actions mType;
  int mVal, mNewLocation, mOldLocation;
  Transition(actions action, int val, int newLocation, int oldLocation);
  Transition(actions action, int val, int newLocation);
  Transition(const Transition& other);
};

}  // end namespace tzfe_engine;

#endif  // TZFE_GAME_TRANSITION_HPP_
