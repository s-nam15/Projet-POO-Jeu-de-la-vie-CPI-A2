#include <iostream>
#include <cassert>
#include <fstream>
#include "Grid.h"
#include "ConwayRule.h"
#include "AliveCell.h"
#include "DeadCell.h"
#include "Game.h"

// Test 1: Règle de naissance
void testBirthRule() {
    std::cout << "Test 1: Regle de naissance... ";
    ConwayRule rule;
    DeadCell cell;
    assert(rule.computeNextState(&cell, 3) == true);
    std::cout << "PASS" << std::endl;
}

// Test 2: Survie avec 2 voisins
void testSurvivalWith2() {
    std::cout << "Test 2: Survie avec 2 voisins... ";
    ConwayRule rule;
    AliveCell cell;
    assert(rule.computeNextState(&cell, 2) == true);
    std::cout << "PASS" << std::endl;
}

// Test 3: Survie avec 3 voisins
void testSurvivalWith3() {
    std::cout << "Test 3: Survie avec 3 voisins... ";
    ConwayRule rule;
    AliveCell cell;
    assert(rule.computeNextState(&cell, 3) == true);
    std::cout << "PASS" << std::endl;
}

// Test 4: Mort par sous-population
void testUnderpopulation() {
    std::cout << "Test 4: Mort sous-population... ";
    ConwayRule rule;
    AliveCell cell;
    assert(rule.computeNextState(&cell, 0) == false);
    assert(rule.computeNextState(&cell, 1) == false);
    std::cout << "PASS" << std::endl;
}

// Test 5: Mort par surpopulation
void testOverpopulation() {
    std::cout << "Test 5: Mort surpopulation... ";
    ConwayRule rule;
    AliveCell cell;
    assert(rule.computeNextState(&cell, 4) == false);
    assert(rule.computeNextState(&cell, 5) == false);
    std::cout << "PASS" << std::endl;
}

// Test 6: Comptage des voisins
void testNeighborCounting() {
    std::cout << "Test 6: Comptage voisins... ";
    
    // Créer un fichier temporaire avec un pattern connu
    std::ofstream file("test_pattern.txt");
    file << "3 3\n";
    file << "0 1 0\n";
    file << "1 1 1\n";
    file << "0 1 0\n";
    file.close();
    
    Grid grid;
    grid.loadFile("test_pattern.txt");
    
    // La cellule centrale (1,1) doit avoir 4 voisins vivants
    int neighbors = grid.countAliveNeighbors(1, 1);
    assert(neighbors == 4);
    
    std::cout << "PASS" << std::endl;
}

// Test 7: Pattern Block (stable)
void testBlockPattern() {
    std::cout << "Test 7: Pattern Block stable... ";
    
    // Créer un block 2x2
    std::ofstream file("test_block.txt");
    file << "4 4\n";
    file << "0 0 0 0\n";
    file << "0 1 1 0\n";
    file << "0 1 1 0\n";
    file << "0 0 0 0\n";
    file.close();
    
    Grid grid;
    grid.loadFile("test_block.txt");
    
    ConwayRule rule;
    Grid* before = grid.clone();
    
    // Appliquer les règles
    grid.applyRules(&rule);
    grid.update();
    
    // Le block doit rester identique
    assert(grid.isEqual(*before));
    
    delete before;
    std::cout << "PASS" << std::endl;
}

// Test 8: Pattern Blinker (oscillateur période 2)
void testBlinkerPattern() {
    std::cout << "Test 8: Pattern Blinker... ";
    
    // Créer un blinker vertical
    std::ofstream file("test_blinker.txt");
    file << "5 5\n";
    file << "0 0 0 0 0\n";
    file << "0 0 1 0 0\n";
    file << "0 0 1 0 0\n";
    file << "0 0 1 0 0\n";
    file << "0 0 0 0 0\n";
    file.close();
    
    Grid grid;
    grid.loadFile("test_blinker.txt");
    
    ConwayRule rule;
    Grid* iteration0 = grid.clone();
    
    // Itération 1 : devient horizontal
    grid.applyRules(&rule);
    grid.update();
    assert(!grid.isEqual(*iteration0)); // Doit changer
    
    Grid* iteration1 = grid.clone();
    
    // Itération 2 : redevient vertical
    grid.applyRules(&rule);
    grid.update();
    assert(grid.isEqual(*iteration0)); // Doit revenir à l'état initial
    assert(!grid.isEqual(*iteration1)); // Différent de l'itération 1
    
    delete iteration0;
    delete iteration1;
    std::cout << "PASS" << std::endl;
}

// Test 9: Simulation complète avec Game
void testGameSimulation() {
    std::cout << "Test 9: Simulation complete... ";
    
    // Créer un fichier de test
    std::ofstream file("test_game.txt");
    file << "5 5\n";
    file << "0 0 1 0 0\n";
    file << "0 0 0 1 0\n";
    file << "0 1 1 1 0\n";
    file << "0 0 0 0 0\n";
    file << "0 0 0 0 0\n";
    file.close();
    
    // Créer un jeu en mode console avec 5 itérations
    Game game(5, 0, "test_game.txt");
    game.loadGame();
    
    Grid* initialGrid = game.getGrid()->clone();
    
    // L'itération doit être 0 au début
    assert(game.getCurrentIteration() == 0);
    
    delete initialGrid;
    std::cout << "PASS" << std::endl;
}

// Test 10: Fichiers de sortie
void testOutputFiles() {
    std::cout << "Test 10: Creation fichiers sortie... ";
    
    std::ofstream file("test_output.txt");
    file << "3 3\n";
    file << "0 1 0\n";
    file << "0 1 0\n";
    file << "0 1 0\n";
    file.close();
    
    Grid grid;
    grid.loadFile("test_output.txt");
    
    // Sauvegarder
    grid.saveToFile("test_output_result.txt");
    
    // Recharger et vérifier
    Grid grid2;
    grid2.loadFile("test_output_result.txt");
    
    assert(grid.isEqual(grid2));
    
    std::cout << "PASS" << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   TESTS UNITAIRES - JEU DE LA VIE    " << std::endl;
    std::cout << "========================================\n" << std::endl;

    try {
        testBirthRule();
        testSurvivalWith2();
        testSurvivalWith3();
        testUnderpopulation();
        testOverpopulation();
        testNeighborCounting();
        testBlockPattern();
        testBlinkerPattern();
        testGameSimulation();
        testOutputFiles();
        
        std::cout << "\n========================================" << std::endl;
        std::cout << "   TOUS LES TESTS SONT PASSES ! ✓     " << std::endl;
        std::cout << "========================================" << std::endl;
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\nERREUR: " << e.what() << std::endl;
        return 1;
    }
}