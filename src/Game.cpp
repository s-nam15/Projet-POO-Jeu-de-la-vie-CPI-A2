#include "Game.h"
#include "ConwayRule.h"
#include "ConsoleRenderer.h"
#include <iostream>
#include <filesystem>

Game::Game(Grid initial, std::unique_ptr<RuleSet> rules, std::unique_ptr<Renderer> renderer)
    : grid_(std::move(initial)), rules_(std::move(rules)), renderer_(std::move(renderer)) {}

bool Game::isStable() const {
    // pour simplifier, on ne peut pas comparer ici sans calculer la prochaine grille (méthode non const)
    return false;
}

void Game::runConsole(int maxIterations) {
    Grid current = grid_;
    
    std::string base = "output/";
    std::filesystem::create_directory(base);

    for (int iter = 0; iter < maxIterations; ++iter) {
        std::cout << "Iteration " << iter << ":\n";
        renderer_->render(current);

        // Génération du fichier de sortie
        std::string filename = base + "iteration_" + std::to_string(iter) + ".txt";
        renderer_->saveToFile(current, filename);

        Grid next = current.computeNextGrid(*rules_);

        if (next == current) {
            std::cout << "Stable après " << iter << " itérations.\n";
            break;
        }

        current = next;
    }
}
