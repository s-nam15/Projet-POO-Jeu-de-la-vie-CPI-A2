#include "ConwayRule.h"
// Implémente les règles classiques du Jeu de la Vie de Conway
bool ConwayRule::computeNextState(const Cell* cell, int aliveNeighbors) const {
    if (cell->isAlive()) {
        return (aliveNeighbors == 2 || aliveNeighbors == 3);
    } else {
        return (aliveNeighbors == 3);
    }
}