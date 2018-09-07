// Created by steve Richards on 06/09/18.

#include "transition.h"

/*
 * Below are the implementation methods for the Transition object.
 */
Transition::Transition(actions action, int val, int newLocation, int oldLocation) {
    this->type = action;
    this->val = val;
    this->newLocation = newLocation;
    this->oldLocation = oldLocation;
}

Transition::Transition(actions action, int val, int newLocation) {
    this->type = action;
    this->val = val;
    this->newLocation = newLocation;
}
