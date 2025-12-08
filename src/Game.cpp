#include "Game.h"
#include "ConwayRule.h"
#include "ConsoleView.h"
#include "GUIView.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

Game::Game(int iter, int mode, const std::string& input)
    : grid(nullptr), rule(nullptr), iterations(iter), 
      currentIteration(0), mode(mode), inputFile(input), previousGrid(nullptr) { // inputFile = "grid_glider.txt"
    rule = new ConwayRule();
}

Game::~Game() {
    delete grid;
    delete rule;
    delete previousGrid;
}

// Création d'objet Grid et lire les états de la grille dans fichier "grid_glider.txt"
void Game::loadGame() {
    grid = new Grid();
    grid->loadFile(inputFile); // Lire le fichier "grid_glider.txt" et la grille chargée stocke dans le Game
    std::cout << "Grille chargée: " << grid->getRows() << "x" << grid->getCols() << std::endl; // ex) Grille chargée: 20x20
}

void Game::runConsole() {
    ConsoleView view;
    view.setGame(this);
    
    std::string baseName = inputFile.substr(inputFile.find_last_of("/\\") + 1);
    size_t dotPos = baseName.find_last_of('.');
    if (dotPos != std::string::npos) {
        baseName = baseName.substr(0, dotPos);
    }
    
    std::string outputDir = baseName + "_out";
    if (!fs::exists(outputDir)) {
        fs::create_directory(outputDir);
    }
    
    std::cout << "Mode console - Simulation de " << iterations << " itérations" << std::endl;
    
    std::string filename = outputDir + "/iteration_0.txt";
    grid->saveToFile(filename);
    view.printToConsole();
    
    while (!isFinished()) {
        currentIteration++;
        
        if (previousGrid) delete previousGrid;
        previousGrid = grid->clone();
        
        grid->applyRules(rule);
        grid->update();
        
        std::string filename = outputDir + "/iteration_" + std::to_string(currentIteration) + ".txt";
        grid->saveToFile(filename);
        view.printToConsole();
        
        if (previousGrid && grid->isEqual(*previousGrid)) {
            std::cout << "Grille stabilisee a l'iteration " << currentIteration << std::endl;
            break;
        }
    }
    
    std::cout << "Simulation terminee apres " << currentIteration << " iterations" << std::endl;
    std::cout << "Resultats sauvegardes dans: " << outputDir << std::endl;
}

void Game::runGraphic() {
    GUIView view;
    view.setGame(this);
    std::cout << "Mode graphique non disponible" << std::endl;
    view.render();
}

void Game::run() {
    if (mode == 0) {
        runConsole();
    } else {
        runGraphic();
    }
}

bool Game::isFinished() const {
    return currentIteration >= iterations;
}

Grid* Game::getGrid() const {
    return grid;
}

int Game::getCurrentIteration() const {
    return currentIteration;
}

Rule* Game::getRule() const {
    return rule;
}

void Game::incrementIteration() {
    currentIteration++;
}