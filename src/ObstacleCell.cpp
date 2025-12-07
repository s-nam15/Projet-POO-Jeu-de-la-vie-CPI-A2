#include "ObstacleCell.h"

ObstacleCell::ObstacleCell(bool isAlive) : Cell(isAlive) {
    // Fixer l'état initial
    nextState = isAlive;
}

Cell* ObstacleCell::clone() const {
    return new ObstacleCell(*this);
}

void ObstacleCell::setNextState(bool state) {
    // NE RIEN FAIRE - l'obstacle reste fixe
    (void)state; // Ignorer le paramètre
    nextState = alive; // Toujours garder l'état actuel
}