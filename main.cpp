//============================================================================
// Name        : main.cpp
// Author      : Steve Richards
// Created on  : 06/09/18.
// Version     : 0.1a
// Copyright   : TBA
// Description : Executing program to run 2048 console game.
//============================================================================

#include "twozerofoureight.h"
#include "userinput.h"

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


int main() {

	// define some strings
	const char* clearScrn     = "clear";
 	const char* prompt        = "\n\t*** Let's PLAY!! *** Actions:[ arrows(left, right, up, down), n=new game, q=quit]\n";
	const char* nilSlideLeft  = " - CAN'T SLIDE OR COMPACT ANY MORE LEFT!";
	const char* nilSlideRight = " - CAN'T SLIDE OR COMPACT ANY MORE RIGHT!";
	const char* nilSlideUp    = " - CAN'T SLIDE OR COMPACT ANY MORE UP!";
	const char* nilSlideDown  = " - CAN'T SLIDE OR COMPACT ANY MORE DOWN!";
	const char* invalidAction = "invalid action. Please try again!";
	const char* quitMsg       = "\n\n\t*** Thanks for playing :)  Come again! ***\n\n";
	const char* youLose       = "\n\t*** GAME OVER -> YOU LOSE. NO MOVES REMAINING. PRESS ENTER FOR NEW GAME: ***\n";
	const char* youWin        = "\n\t*** YOU DA WINNER  !!!AWESOME!!!  PRESS ENTER FOR NEW GAME: ***\n";

	
	// Create new game engine object and output to fresh screen.
    system(clearScrn); 
	TwoZeroFourEight tzfe = TwoZeroFourEight();
    cout << tzfe.toString() << "\n\n" << endl;
 
 	// Output prompt and take move input from the user
 	cout << prompt;
	char input = userInput();
	
	// Listen to user input until user quits.
	while (true) {

		input = userInput();  // get unbuffered user input.	
		string action = "\n\tLast action: ";
		
		switch (input) {
			case 'D':
				action += "move left";
				if (!tzfe.actionMove(LEFT)) action += nilSlideLeft;
				break;
			case 'C':
				action += "move right";
				if (!tzfe.actionMove(RIGHT)) action += nilSlideRight; 
				break;
			case 'A':
				action += "move up";
				if (!tzfe.actionMove(UP)) action += nilSlideUp;
				break;
			case 'B':
				action += "move down";
				if (!tzfe.actionMove(DOWN)) action += nilSlideDown;
				break;
			case 'n':
				tzfe = TwoZeroFourEight();
				action += "start new game";
				break;
			case 'q':
				system(clearScrn); 
				cout << tzfe.toString() << endl;
				action += "Quit game";
				action += quitMsg;
				cout << action;
				return 0;  // Exit the game program here.
				break;
			default:
				action += invalidAction;
				break;
		}

		// Clear screen and output updated game board resulting from last input action.
		system(clearScrn);
		cout << tzfe.toString() << endl;
		cout << action << endl;

		// Check the result of the last move request: 
		// ??? Has the user Lost or Won the game yet ???
		string dummyStr;
		if (!tzfe.hasMovesRemaining()) {
		 	cout << youLose;
			getline(cin, dummyStr);
			system(clearScrn);
			tzfe = TwoZeroFourEight();
			cout << tzfe.toString() << "\n\n" << endl;
	 		cout << prompt;			
		} else if (tzfe.gameWon ()) {
		 	cout << youWin;
			getline(cin, dummyStr);	
			system(clearScrn); 
			tzfe = TwoZeroFourEight();
			cout << tzfe.toString() << "\n\n" << endl;
	 		cout << prompt;	
		} else {
	 		cout << prompt;
	 	}
	}
	
    return 0;
}
