#ifndef GAME_H
#define GAME_H

#include <string>
#include "Grid.h"
#include "Rule.h"
#include "View.h"

class Game {
private:
    Grid* grid;
    Rule* rule;
    int iterations;
    int currentIteration;
    int mode;
    std::string inputFile;
    Grid* previousGrid;

public:
    Game(int iter, int mode, const std::string& input);
    ~Game();
    void loadGame();
    void runConsole();
    void runGraphic();
    void run();
    bool isFinished() const;
    Grid* getGrid() const;
    int getCurrentIteration() const;
    Rule* getRule() const;
    void incrementIteration();
};

#endif