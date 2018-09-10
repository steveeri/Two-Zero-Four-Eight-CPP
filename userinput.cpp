//============================================================================
// Name        : userinput.cpp
// Author      : Steve Richards
// Created on  : 10/09/18.
// Version     : 0.1a
// Copyright   : TBA
// Description : Reads the unbuffered keyboard inputs from the terminal. [ Linux ]
//============================================================================

#include <iostream>
#include <unistd.h>
#include <termios.h>

// Read character from keypresses. 
// Toggle Echo & Canonical modes before and after read to to supress character display.
char userInput() {

	// Set terminal attributes for Nil Echo & Canonical.
    struct termios tmAttrs = {0};	
    if (tcgetattr(0, &tmAttrs) < 0) perror("tcsetattr()");
    tmAttrs.c_lflag &= ~ICANON;
    tmAttrs.c_lflag &= ~ECHO;
    tmAttrs.c_cc[VMIN] = 1;
    tmAttrs.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &tmAttrs) < 0) perror("tcsetattr ICANON");

	// Read keyboard input buffer. Restore Nil Echo & Canonical.
    char buf = 0;
	if (read(0, &buf, 1) < 0) perror("read()");
    tmAttrs.c_lflag |= ICANON;
    tmAttrs.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &tmAttrs) < 0) perror("tcsetattr ~ICANON");

	return (buf); // return input.
}