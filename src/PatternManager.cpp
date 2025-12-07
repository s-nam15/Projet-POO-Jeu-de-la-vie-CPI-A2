#include "PatternManager.h"
#include "AliveCell.h"
#include "DeadCell.h"

void PatternManager::setCell(Grid* grid, int row, int col, bool alive) {
    if (row < 0 || row >= grid->getRows() || col < 0 || col >= grid->getCols()) {
        return;
    }
    
    Cell* currentCell = grid->getCell(row, col);
    if (currentCell) {
        currentCell->setNextState(alive);
        currentCell->updateState();
    }
}

void PatternManager::placeGlider(Grid* grid, int row, int col) {
    // Glider :
    //   X
    //    X
    //  XXX
    setCell(grid, row, col + 1, true);
    setCell(grid, row + 1, col + 2, true);
    setCell(grid, row + 2, col, true);
    setCell(grid, row + 2, col + 1, true);
    setCell(grid, row + 2, col + 2, true);
}

void PatternManager::placeBlinker(Grid* grid, int row, int col) {
    // Blinker vertical :
    //  X
    //  X
    //  X
    setCell(grid, row, col, true);
    setCell(grid, row + 1, col, true);
    setCell(grid, row + 2, col, true);
}

void PatternManager::placeBlock(Grid* grid, int row, int col) {
    // Block 2x2 :
    //  XX
    //  XX
    setCell(grid, row, col, true);
    setCell(grid, row, col + 1, true);
    setCell(grid, row + 1, col, true);
    setCell(grid, row + 1, col + 1, true);
}

void PatternManager::placeToad(Grid* grid, int row, int col) {
    // Toad :
    //   XXX
    //  XXX
    setCell(grid, row, col + 1, true);
    setCell(grid, row, col + 2, true);
    setCell(grid, row, col + 3, true);
    setCell(grid, row + 1, col, true);
    setCell(grid, row + 1, col + 1, true);
    setCell(grid, row + 1, col + 2, true);
}

void PatternManager::placeBeacon(Grid* grid, int row, int col) {
    // Beacon :
    //  XX
    //  XX
    //    XX
    //    XX
    setCell(grid, row, col, true);
    setCell(grid, row, col + 1, true);
    setCell(grid, row + 1, col, true);
    setCell(grid, row + 2, col + 3, true);
    setCell(grid, row + 3, col + 2, true);
    setCell(grid, row + 3, col + 3, true);
}