#include "ConwayRule.h"

bool ConwayRule::computeNextState(const Cell* cell, int aliveNeighbors) const {
    if (cell->isAlive()) {
        return (aliveNeighbors == 2 || aliveNeighbors == 3);
    } else {
        return (aliveNeighbors == 3);
    }
}