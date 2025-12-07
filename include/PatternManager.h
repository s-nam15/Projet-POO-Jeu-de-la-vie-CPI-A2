#ifndef PATTERNMANAGER_H
#define PATTERNMANAGER_H

#include "Grid.h"
#include <vector>
#include <string>

class PatternManager {
public:
    // Motifs prédéfinis
    static void placeGlider(Grid* grid, int row, int col);
    static void placeBlinker(Grid* grid, int row, int col);
    static void placeBlock(Grid* grid, int row, int col);
    static void placeToad(Grid* grid, int row, int col);
    static void placeBeacon(Grid* grid, int row, int col);
    
private:
    static void setCell(Grid* grid, int row, int col, bool alive);
};

#endif