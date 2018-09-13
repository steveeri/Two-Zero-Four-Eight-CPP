//============================================================================
// Name        : twozerofoureight.cpp
// Author      : Steve Richards
// Created on  : 06/09/18.
// Version     :
// Copyright   : Your copyright notice
// Description : 2048 Game engine implementation files
//============================================================================

#include "twozerofoureight.hpp"

#include <cstdlib>
#include <iostream>

namespace tzfe_engine {

//
// Below are the implementation methods for the TwoZeroFourEight game class.
// The tiles game grid is organised from bottom row left to right columns, bottom to top rows
// columns left to right.
//

void TwoZeroFourEight::createNewTransitions() {
  mTransitions = std::vector<tzfe_engine::Transition>();
  mTransitions.reserve(30);
}

void TwoZeroFourEight::rePlot() {
  createNewTransitions();
  for (int i = 0; i < GRID_CNT; i++) {
    mTransitions.emplace_back(REFRESH, mTiles[i], i);
  }
}

//private method
bool TwoZeroFourEight::addNewTile() {
  if (mNumEmpty == 0) return (false);

  // Initialise random number generator
  time_t t;
  srand(
      static_cast<unsigned>(time(&t)) + static_cast<unsigned>(mMaxTile)
          + static_cast<unsigned>(mScore));

  int val = ((rand() % 2) + 1) * 2;
  int pos = rand() % mNumEmpty;
  int numBlanksFound = 0;

  for (int i = 0; i < GRID_CNT; i++) {
    if (mTiles[i] == BLANK) {
      if (numBlanksFound == pos) {
        mTiles[i] = val;
        if (val > mMaxTile) mMaxTile = val;
        mTransitions.emplace_back(ADD, val, i);
        mNumEmpty--;
        return (true);
      }
      numBlanksFound++;
    }
  }
  return (false);
}

// Private method
bool TwoZeroFourEight::slideTileRowOrColumn(int index1, int index2, int index3, int index4) {

  bool moved = false;
  int tmpArr[GRID_SIZE] = { index1, index2, index3, index4 };

  // Do we have some sliding to do, or not?
  int es = 0;  // empty spot index
  for (int j = 1; j < GRID_SIZE; j++) {
    if (mTiles[tmpArr[es]] != BLANK) {
      es++;
    } else if (mTiles[tmpArr[j]] == BLANK) {
      continue;
    } else {
      // Otherwise we have a slide condition
      mTiles[tmpArr[es]] = mTiles[tmpArr[j]];
      mTiles[tmpArr[j]] = BLANK;
      mTransitions.emplace_back(SLIDE, mTiles[tmpArr[es]], tmpArr[es], tmpArr[j]);
      mTransitions.emplace_back(CLEAR, (int) BLANK, tmpArr[j]);
      moved = true;
      es++;
    }
  }
  return (moved);
}

// Private method
bool TwoZeroFourEight::compactTileRowOrColumn(int index1, int index2, int index3, int index4) {

  bool compacted = false;
  int tmpArr[GRID_SIZE] = { index1, index2, index3, index4 };

  for (int j = 0; j < (GRID_SIZE - 1); j++) {

    if (mTiles[tmpArr[j]] != BLANK && mTiles[tmpArr[j]] == mTiles[tmpArr[j + 1]]) { // we found a matching pair
      int ctv = mTiles[tmpArr[j]] * 2;   // = compacted tile value
      mTiles[tmpArr[j]] = ctv;
      mTiles[tmpArr[j + 1]] = BLANK;
      mScore += ctv;
      if (ctv > mMaxTile) {
        mMaxTile = ctv;
      }  // is this the biggest tile # so far
      mTransitions.emplace_back(COMPACT, ctv, tmpArr[j], tmpArr[j + 1]);
      mTransitions.emplace_back(CLEAR, (int) BLANK, tmpArr[j + 1]);
      compacted = true;
      mNumEmpty++;
    }
  }
  return (compacted);
}

// Private method
bool TwoZeroFourEight::slideLeft() {
  bool a = slideTileRowOrColumn(0, 4, 8, 12);
  bool b = slideTileRowOrColumn(1, 5, 9, 13);
  bool c = slideTileRowOrColumn(2, 6, 10, 14);
  bool d = slideTileRowOrColumn(3, 7, 11, 15);
  return (a || b || c || d);
}

// Private method
bool TwoZeroFourEight::slideRight() {
  bool a = slideTileRowOrColumn(12, 8, 4, 0);
  bool b = slideTileRowOrColumn(13, 9, 5, 1);
  bool c = slideTileRowOrColumn(14, 10, 6, 2);
  bool d = slideTileRowOrColumn(15, 11, 7, 3);
  return (a || b || c || d);
}

// Private method
bool TwoZeroFourEight::slideUp() {
  bool a = slideTileRowOrColumn(0, 1, 2, 3);
  bool b = slideTileRowOrColumn(4, 5, 6, 7);
  bool c = slideTileRowOrColumn(8, 9, 10, 11);
  bool d = slideTileRowOrColumn(12, 13, 14, 15);
  return (a || b || c || d);
}

// Private method
bool TwoZeroFourEight::slideDown() {
  bool a = slideTileRowOrColumn(3, 2, 1, 0);
  bool b = slideTileRowOrColumn(7, 6, 5, 4);
  bool c = slideTileRowOrColumn(11, 10, 9, 8);
  bool d = slideTileRowOrColumn(15, 14, 13, 12);
  return (a || b || c || d);
}

// Private method
bool TwoZeroFourEight::compactLeft() {
  bool a = compactTileRowOrColumn(0, 4, 8, 12);
  bool b = compactTileRowOrColumn(1, 5, 9, 13);
  bool c = compactTileRowOrColumn(2, 6, 10, 14);
  bool d = compactTileRowOrColumn(3, 7, 11, 15);
  return (a || b || c || d);
}

// Private method
bool TwoZeroFourEight::compactRight() {
  bool a = compactTileRowOrColumn(12, 8, 4, 0);
  bool b = compactTileRowOrColumn(13, 9, 5, 1);
  bool c = compactTileRowOrColumn(14, 10, 6, 2);
  bool d = compactTileRowOrColumn(15, 11, 7, 3);
  return (a || b || c || d);
}

// Private method
bool TwoZeroFourEight::compactUp() {
  bool a = compactTileRowOrColumn(0, 1, 2, 3);
  bool b = compactTileRowOrColumn(4, 5, 6, 7);
  bool c = compactTileRowOrColumn(8, 9, 10, 11);
  bool d = compactTileRowOrColumn(12, 13, 14, 15);
  return (a || b || c || d);
}

// Private method
bool TwoZeroFourEight::compactDown() {
  bool a = compactTileRowOrColumn(3, 2, 1, 0);
  bool b = compactTileRowOrColumn(7, 6, 5, 4);
  bool c = compactTileRowOrColumn(11, 10, 9, 8);
  bool d = compactTileRowOrColumn(15, 14, 13, 12);
  return (a || b || c || d);
}

// Private method
bool TwoZeroFourEight::actionMoveLeft() {
  bool a = slideLeft();
  bool b = compactLeft();
  bool c = slideLeft();
  return (a || b || c);
}

// Private method
bool TwoZeroFourEight::actionMoveRight() {
  bool a = slideRight();
  bool b = compactRight();
  bool c = slideRight();
  return (a || b || c);
}

// Private method
bool TwoZeroFourEight::actionMoveUp() {
  bool a = slideUp();
  bool b = compactUp();
  bool c = slideUp();
  return (a || b || c);
}

// Private method
bool TwoZeroFourEight::actionMoveDown() {
  bool a = slideDown();
  bool b = compactDown();
  bool c = slideDown();
  return (a || b || c);
}

// Public method to Check if there are any moves remaining.
bool TwoZeroFourEight::hasMovesRemaining() {

  if (mNumEmpty > 0) return (true);

  // check left-right for compact moves remaining.
  int arrLimit = GRID_CNT - COL_CNT;
  for (int i = 0; i < arrLimit; i++) {
    if (mTiles[i] == mTiles[i + COL_CNT]) return (true);
  }

  // check up-down for compact moves remaining.
  arrLimit = GRID_CNT - 1;
  for (int i = 0; i < arrLimit; i++) {
    if ((i + 1) % ROW_CNT > 0) {
      if (mTiles[i] == mTiles[i + 1]) return (true);
    }
  }
  return (false);
}

// Public method used to action a users selected move type
bool TwoZeroFourEight::actionMove(Moves move) {

  this->createNewTransitions();
  if (!this->hasMovesRemaining()) return (false);

  bool result = false;
  switch (move) {
  case LEFT:
    result = actionMoveLeft();
    break;
  case RIGHT:
    result = actionMoveRight();
    break;
  case UP:
    result = actionMoveUp();
    break;
  case DOWN:
    result = actionMoveDown();
    break;
  }

  if (result) this->addNewTile();
  return (result);
}

// Output a text representation of the current state of the game board.
std::string TwoZeroFourEight::toString() {

  //using namespace std::to_string = toString;

  std::string strVals[GRID_CNT];

  for (int i = 0; i < GRID_CNT; i++) {

    std::string tmpStr = std::to_string(mTiles[i]);
    unsigned long strLen = tmpStr.length();
    switch (strLen) {
    case 1:
      tmpStr = "| " + tmpStr + "  ";
      break;
    case 2:
      tmpStr = "| " + tmpStr + " ";
      break;
    case 3:
      tmpStr = "| " + tmpStr;
      break;
    default:
      tmpStr = "|" + tmpStr;
    }

    if (i >= 12) {
      tmpStr += "|\n";
    }
    strVals[i] = tmpStr;
  }

  // Compile the output data.
  std::string str = "\n         [[[ 2048 ]]]\n\n";
  str += "\n           Score: " + std::to_string(mScore);
  str += "\n        Max Tile: " + std::to_string(mMaxTile);
  str += "\n       ---------------------\n";
  str += "       " + strVals[0] + strVals[4] + strVals[8] + strVals[12];
  str += "       " + strVals[1] + strVals[5] + strVals[9] + strVals[13];
  str += "       " + strVals[2] + strVals[6] + strVals[10] + strVals[14];
  str += "       " + strVals[3] + strVals[7] + strVals[11] + strVals[15];
  str += "       ---------------------\n";
  return (str);
}

} // end namespace tzfe_engine

