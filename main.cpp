//============================================================================
// Name        : main.cpp
// Author      : Steve Richards
// Version     : 0.1a
// Copyright   : TBA
// Description : Executing program to run 2048 console game.
//============================================================================

#include "twozerofoureight.h"

#include <iostream>
#include <cstdlib>
#include <string>


using namespace std;

int main() 
{
    TwoZeroFourEight tzfe = TwoZeroFourEight();
    
	system("clear"); 
    cout << tzfe.toString() << "\n\n" << endl;
 
 	// Take move inpute from the user
 	string prompt = "\n\t*** Let's PLAY!! ***\n\n\t    Actions:[ arrows(left, right, up, down), n=new game, q=quit]. please enter: ";
 	cout << prompt;

	string line;
	
	while (true) {

		getline(std::cin, line);
		
		if (line.length() == 0) { 
			line = " ";
		}
						
		char input = line.at(0);
		
		if (input == '\033' && line.length() > 2) { 
			input = line.at(2);		
		}
			
	    //cout << input << endl;
	
		string action = "\n\tLast action: ";	
		switch (input) {
			case 'D':
				action += "move left";
				if (!tzfe.actionMove(LEFT)) action += " - CAN'T SLIDE OR COMPACT ANY MORE LEFT!";
				break;
			case 'C':
				action += "move right";
				if (!tzfe.actionMove(RIGHT)) action += " - CAN'T SLIDE OR COMPACT ANY MORE RIGHT!"; 
				break;
			case 'A':
				action += "move up";
				if (!tzfe.actionMove(UP)) action += " - CAN'T SLIDE OR COMPACT ANY MORE UP!";
				break;
			case 'B':
				action += "move down";
				if (!tzfe.actionMove(DOWN)) action += " - CAN'T SLIDE OR COMPACT ANY MORE DOWN!";
				break;
			case 'n':
				tzfe = TwoZeroFourEight();
				action += "start new game";
				break;
			case 'q':
				action = "\n\t*** Thanks for playing :)  Come again! ***\n\n";
				cout << action;
				return 0;
				break;
			default:
				action += "invalid action. Please try again!";
				break;
		}
		
		system("clear");
		cout << tzfe.toString() << endl;
		cout << action << endl;
		
		if (!tzfe.hasMovesRemaining()) {
		 	cout << "\n\t*** GAME OVER -> YOU LOSE. NO MOVES REMAINING. PRESS ANY KEY FOR NEW GAME: ***\n";
			getline(std::cin, line);
			system("clear"); 
			tzfe = TwoZeroFourEight();
			cout << tzfe.toString() << "\n\n" << endl;
	 		cout << prompt;			
		} else if (tzfe.getMaxTile() >= 2048) {
		 	cout << "\n\t*** YOU DA WINNER  !!!AWESOME!!!  PRESS ANY KEY FOR NEW GAME: ***\n";
			getline(std::cin, line);		
			system("clear"); 
			tzfe = TwoZeroFourEight();
			cout << tzfe.toString() << "\n\n" << endl;
	 		cout << prompt;			
		} else {
	 		cout << prompt;
	 	}
	}
	
    return 0;
}
