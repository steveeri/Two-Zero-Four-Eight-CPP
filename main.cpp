//============================================================================
// Name        : main.cpp
// Author      : Steve Richards
// Created on  : 06/09/18.
// Version     : 0.1a
// Copyright   : TBA
// Description : Executing program to run 2048 console game.
//============================================================================

#include "twozerofoureight.hpp"
#include <iostream>
#include <cstdlib>
#include <string>
#include <curses.h>
#include "terminalutility.hpp"

int main() {

  using namespace tzfe_engine;

  setlocale(LC_ALL, "");

  // define some strings
  const char* clearScrn = "clear";
  const char* prompt =
      "\n\t*** Let's PLAY!! *** Actions:[ arrows(left, right, up, down), n=new game, q=quit]\n";
  const char* nilSlideLeft = " - CAN'T SLIDE OR COMPACT ANY MORE LEFT!";
  const char* nilSlideRight = " - CAN'T SLIDE OR COMPACT ANY MORE RIGHT!";
  const char* nilSlideUp = " - CAN'T SLIDE OR COMPACT ANY MORE UP!";
  const char* nilSlideDown = " - CAN'T SLIDE OR COMPACT ANY MORE DOWN!";
  const char* invalidAction = "invalid action. Please try again!";
  const char* quitMsg = "\n\n\t*** Thanks for playing :)  Come again! ***\n\n";
  const char* youLose =
      "\n\t*** GAME OVER -> YOU LOSE. NO MOVES REMAINING. PRESS ENTER FOR NEW GAME: ***\n";
  const char* youWin = "\n\t*** YOU DA WINNER  !!!AWESOME!!!  PRESS ENTER FOR NEW GAME: ***\n";

  // Create new game engine object and output to fresh screen.
  TerminalUtility tu;
  tu.clearScreen();
  TwoZeroFourEight* pTzfe = new TwoZeroFourEight();
  std::cout << pTzfe->toString() << "\n\n" << std::endl;

  // Output prompt and take move input from the user
  std::cout << prompt;

  // Listen to user input until user quits.
  while (true) {

    char input = tu.userInput();  // get unbuffered user input.
    std::string action = "\n\tLast action: ";

    switch (input) {
    case 'D':
      action += "move left";
      if (!pTzfe->actionMove(LEFT)) action += nilSlideLeft;
      break;
    case 'C':
      action += "move right";
      if (!pTzfe->actionMove(RIGHT)) action += nilSlideRight;
      break;
    case 'A':
      action += "move up";
      if (!pTzfe->actionMove(UP)) action += nilSlideUp;
      break;
    case 'B':
      action += "move down";
      if (!pTzfe->actionMove(DOWN)) action += nilSlideDown;
      break;
    case 'n':
      delete pTzfe;
      pTzfe = new TwoZeroFourEight();
      action += "start new game";
      break;
    case 'q':
      system(clearScrn);
      std::cout << pTzfe->toString() << std::endl;
      action += "Quit game";
      action += quitMsg;
      std::cout << action;
      return (0);  // Exit the game program here.
    default:
      action += invalidAction;
      break;
    }

    // Clear screen and output updated game board resulting from last input action.
    tu.clearScreen();
    std::cout << pTzfe->toString() << std::endl;
    std::cout << action << std::endl;

    // Check the result of the last move request:
    // Has the user Lost or Won the game yet?
    std::string dummyStr;
    if (!pTzfe->hasMovesRemaining()) {
      std::cout << youLose;
      getline(std::cin, dummyStr); // use getline to force user enter input. Input value ignored.
      tu.clearScreen();
      delete pTzfe;
      pTzfe = new TwoZeroFourEight();
      std::cout << pTzfe->toString() << "\n\n" << std::endl;
      std::cout << prompt;
    } else if (pTzfe->gameWon()) {
      std::cout << youWin;
      getline(std::cin, dummyStr); // use getline to force user enter input. Input value ignored.
      tu.clearScreen();
      delete pTzfe;
      pTzfe = new TwoZeroFourEight();
      std::cout << pTzfe->toString() << "\n\n" << std::endl;
      std::cout << prompt;
    } else {
      std::cout << prompt;
    }
  }

}
