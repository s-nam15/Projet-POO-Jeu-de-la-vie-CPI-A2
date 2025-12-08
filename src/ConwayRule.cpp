#include "ConwayRule.h"

bool ConwayRule::computeNextState(const Cell* cell, int aliveNeighbors) const {
    if (cell->isAlive()) { // Si la cellule est en état vivant actuellement
        return (aliveNeighbors == 2 || aliveNeighbors == 3); // Si la condition est correcte -> true -> reste vivante, sinon devient morte
    } else { // Si la cellule est en état mort actuellement
        return (aliveNeighbors == 3); // Revivre si la condition correcte
    }
}