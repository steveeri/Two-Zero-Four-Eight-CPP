//============================================================================
// Name        : userinput.cpp
// Author      : Steve Richards
// Created on  : 10/09/18.
// Version     : 0.1a
// Copyright   : TBA
// Description : Reads the unbuffered keyboard inputs from the terminal. [ Linux ]
//============================================================================

#include "userinput.hpp"

#include <cstdio>
#include <unistd.h>
#include <termios.h>

namespace tzfe_engine {

    // Read character from keypresses. 
    // Toggle Echo & Canonical modes before and after read to to supress character display.
    char userInput() {

        // Set terminal attributes for Nil Echo & Canonical.
        struct termios tmAttrs;
        tmAttrs.c_iflag = 0;
        if (tcgetattr(0, &tmAttrs) < 0) std::perror("tcsetattr()");
        tmAttrs.c_lflag &= static_cast<unsigned>(~ICANON);
        tmAttrs.c_lflag &= static_cast<unsigned>(~ECHO);
        tmAttrs.c_cc[VMIN] = 1;
        tmAttrs.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &tmAttrs) < 0) std::perror("tcsetattr ICANON");

        // Read keyboard input buffer. Restore Nil Echo & Canonical.
        char buf = 0;
        if (read(0, &buf, 1) < 0) std::perror("read()");
        tmAttrs.c_lflag |= ICANON;
        tmAttrs.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &tmAttrs) < 0) std::perror("tcsetattr ~ICANON");

        return (buf); // return input.
    }

}  // end namespace tzfe_engine;
