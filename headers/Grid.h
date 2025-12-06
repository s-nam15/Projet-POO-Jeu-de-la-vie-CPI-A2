#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>
#include "Cell.h"
#include "Rule.h"

class Grid {
private:
    int rows; // ligne
    int cols; // colonne
    std::vector<Cell*> cells; // cells[0] = (0,0), cells[1] = (1,1)...
    int getIndex(int row, int col) const; /* Si la grille 4x4 : 
                                            (0,0) (0,1) (0,2) (0,3)
                                            (1,0) (1,1) (1,2) (1,3)
                                            (2,0) (2,1) (2,2) (2,3)
                                            (3,0) (3,1) (3,2) (3,3)
                                            getIndex(2,1) -> 2*4+1 = 9
                                            cells[9] = (2,1) 
                                            Simulaire de table de hachage mais non
                                            */

public:
    // Constructeurs
    Grid();
    Grid(int rows, int cols);

    // Destructeur
    ~Grid();

    // Getters
    int getRows() const;
    int getCols() const;
    Cell* getCell(int row, int col) const;

    // Nombre de cellules vivantes parmi les 8 cellules voisines
    int countAliveNeighbors(int row, int col) const;
    
    // Appliquer la règle (calculer nextState de chaque cellule, on ne change pas directement l'état)
    void applyRules(Rule* rule);

    // C'est là ici on change des états de cellules en même temps (alive = nextState)
    void update();

    // Appel l'état initial de la grille à partir d'un fichier texte ("grid_glider.txt")
    void loadFile(const std::string& path);

    // Enregistrer l'état actuel de la grille dans un fichier (ex.: iteration_0.txt, iteration_1.txt...)
    void saveToFile(const std::string& path) const;

    // Comparer tous les états des cellules à ceux d'autres grilles pour test unitaire
    bool isEqual(const Grid& other) const;

    // Copier la grille entière dans un nouvel objet Grid pour préserver l'original lorsque la simulation
    Grid* clone() const;
};

#endif