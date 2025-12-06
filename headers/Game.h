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
    int currentIteration; // itération où on est
    int mode; // 0 = console, 1 = graphique
    std::string inputFile; // Nom du fichier
    Grid* previousGrid; // grille précédente

public:
    Game(int iter, int mode, const std::string& input);
    ~Game();

    void loadGame(); // Initialisation de la grille
    void runConsole();
    void runGraphic();
    void run(); // exécuter selon le mode console ou GUI
    bool isFinished() const; // Vérifier le nombre d'itération est fini
    Grid* getGrid() const;
    int getCurrentIteration() const;
    Rule* getRule() const;
    void incrementIteration(); // currenIteration + 1
};

#endif