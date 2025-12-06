#include "Cell.h"

Cell::Cell(bool isAlive) : alive(isAlive), nextState(isAlive) {}

bool Cell::isAlive() const {
    return alive;
}

bool Cell::getNextState() const {
    return nextState;
}

void Cell::setNextState(bool state) {
    nextState = state;
}

void Cell::updateState() {
    alive = nextState;
}