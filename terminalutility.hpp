#ifndef TZFE_GAME_USERINPUT_HPP_
#define TZFE_GAME_USERINPUT_HPP_

//============================================================================
// Name        : terminalutility.hpp
// Author      : Steve Richards
// Created on  : 06/09/18.
// Version     :
// Copyright   : Your copyright notice
// Description : Definition for utility class to reads keyboard inputs[ Linux ]
//============================================================================

namespace tzfe_engine {

class TerminalUtility {
public:
  void clearScreen();
  char userInput();
};

}

#endif // TZFE_GAME_USERINPUT_HPP_
