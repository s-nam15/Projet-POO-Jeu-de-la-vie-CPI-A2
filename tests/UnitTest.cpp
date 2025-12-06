#include <iostream>
#include <cassert> // pour la fonction assert
#include <vector>
#include "Grid.h"
#include "ConwayRule.h"
#include "Cell.h"

// Définir les cellules vivantes
void setAlive(Grid* grid, int r, int c) {
    Cell* cell = grid->getCell(r, c); // Position de la cellule (ex.: (0,0), (0,1)..)
    
    // Si les cellules ont bien positionné dans intérieur de la grille (ex.: grid->getCell(-1, 3) = nullptr)
    if (cell != nullptr) { 
        cell->setNextState(true); // Définir l'état de la prochaine génération de la cellule comme vivante
        cell->updateState(); // Mettre à jour l'état actuel (alive = nextState)
    }
}


// Test unitaire
void verifyGridState(Grid* initial, Grid* expected, int iterations) {
    ConwayRule rule; 

    // Exécuter le jeu jusqu'à l'itération max défini par utilisateur
    for (int i = 0; i < iterations; i++) {
        initial->applyRules(&rule); // Appliquer la régle de Conway
        initial->update(); // Mettre à jour l'état actuel (alive = nextState)
    }

    // Vérification des résultats
    if (initial->isEqual(*expected)) { // Si le résultat est la même que nous avons attendu d'après n itération
        std::cout << "[PASS] Test unitaire a réussi avec " << iterations << " itération(s)." << std::endl;
    } else { // Sinon
        std::cerr << "[FAIL] L'état de la grille ne correspond pas à l'état attendu !" << std::endl;
        assert(false); // assert error
    }
}


// Test unitaire avec le fichier "grid_glider.txt"
void testGliderFromTextFile() {
    std::cout << "Grille de grid_glier.txt applique.." << std::endl;

    Grid* startGrid = new Grid(); // Créer une grille vide
    
    // Dans le cas exception (ex.: Fichier n'existe pas ou il y a le problème lorsque le programme lit le fichier)
    try { 
        startGrid->loadFile("grid_glider.txt"); // Appliquer la grille de "grid_glider.txt" dans startGrid
    } catch (const std::exception& e) { // Si il y a l'exception dans try
        std::cerr << "Erreur du fichier" << e.what() << std::endl;
        delete startGrid; // Libérer la mémoire pour éviter la fuite de mémoire
        assert(false); // assert error en cas d'échec du chargement
        return;
    }

    // Utilisateur prédéfini la grille attendue d'après n itération pour comparer avec startgrid
    Grid* expectedGrid = new Grid(20, 20);
    setAlive(expectedGrid, 2, 3); // setAlive(expectedGrid, 1, 3); -> pour tester le cas d'échec
    setAlive(expectedGrid, 3, 4);
    setAlive(expectedGrid, 4, 2);
    setAlive(expectedGrid, 4, 3);
    setAlive(expectedGrid, 4, 4);

    // Test unitaire avec 4 itérations
    verifyGridState(startGrid, expectedGrid, 4);
    
    // Libérer la mémoire pour éviter la fuite de mémoire
    delete startGrid; 
    delete expectedGrid;
}


int main() {
    std::cout << "=== Test unitaire commence ===" << std::endl;
    
    testGliderFromTextFile(); 

    std::cout << "=== Test unitaire a terminé ===" << std::endl;
    return 0;
}

// g++ -std=c++17 -I headers tests/UnitTest.cpp src/Grid.cpp src/Cell.cpp src/AliveCell.cpp src/DeadCell.cpp src/ConwayRule.cpp -o run_tests
// ./run_tests