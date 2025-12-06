#include "ConsoleView.h"
#include "Game.h"
#include "Grid.h"
#include "Cell.h"
#include <iostream>

ConsoleView::ConsoleView() : View() {}

void ConsoleView::render() {
    printToConsole();
}

void ConsoleView::printToConsole() {
    if (!game) return;
    Grid* grid = game->getGrid();
    if (!grid) return;
    std::cout << "\n=== Iteration " << game->getCurrentIteration() << " ===" << std::endl;
    for (int i = 0; i < grid->getRows(); ++i) {
        for (int j = 0; j < grid->getCols(); ++j) {
            Cell* cell = grid->getCell(i, j);
            if (cell && cell->isAlive()) {
                std::cout << "█ ";
            } else {
                std::cout << "· ";
            }
        }
        std::cout << std::endl;
    }
}

void ConsoleView::saveToFile(int iteration) {
    if (!game) return;
    Grid* grid = game->getGrid();
    if (!grid) return;
    std::string outputDir = "output_out";
    std::string filename = outputDir + "/iteration_" + std::to_string(iteration) + ".txt";
    try {
        grid->saveToFile(filename);
    } catch (const std::exception& e) {
        std::cerr << "Erreur sauvegarde: " << e.what() << std::endl;
    }
}