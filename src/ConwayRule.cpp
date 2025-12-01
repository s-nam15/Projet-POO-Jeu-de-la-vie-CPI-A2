#include "ConwayRule.h"

bool ConwayRule::applyRule(const Cell& cell, int aliveNeighbors) const {
    if (!cell.isAlive()) {
        return aliveNeighbors == 3;
    } else {
        return aliveNeighbors == 2 || aliveNeighbors == 3;
    }
}
