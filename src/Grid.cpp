#include "Grid.h"
#include "AliveCell.h"
#include "DeadCell.h"
#include <fstream> // pour ouvrir le fichier (ifstream) et écrire dans fichier (ofstream)
#include <stdexcept> // pour throw (exception apparaître)
#include <iostream>

Grid::Grid() : rows(0), cols(0) {} // Grille vide

Grid::Grid(int rows, int cols) : rows(rows), cols(cols) {
    cells.reserve(rows * cols); // Réserver la capacité dans mémoire à l'avance pour efficace
    
    // Créer une grille initiale remplie de DeadCell
    for (int i = 0; i < rows * cols; i++) {
        cells.push_back(new DeadCell()); 
    }
}

// Destructeur pour éviter la fuite de mémoire
Grid::~Grid() {
    for (Cell* cell : cells) {
        delete cell;
    }
    cells.clear();
}

// Calcule de l'indice de cellule pour obtenir la position
int Grid::getIndex(int row, int col) const {
    return row * cols + col;
}

int Grid::getRows() const {
    return rows;
}

int Grid::getCols() const {
    return cols;
}

// Getter la cellule 
Cell* Grid::getCell(int row, int col) const {
    // Si les coordonées sont extérieur de la grille (pour éviter Segfault)
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return nullptr; // Pointeur qui pointe aucune valeur
    }
    return cells[getIndex(row, col)]; // AliveCell ou DeadCell (ex.: cells[9] = AliveCell)
}

// Calcule de nombre de cellules parmi 8 voisines pour utiliser à la régle Conway
int Grid::countAliveNeighbors(int row, int col) const {
    int count = 0;
    for (int dr = -1; dr <= 1; ++dr) { // dr = delta row
        for (int dc = -1; dc <= 1; ++dc) { // dc = delta col
            if (dr == 0 && dc == 0) continue; // On passe car c'est la cellule centre (0,0) soi-même
            int newRow = row + dr; // Nouvelle ligne déplacée par dr à partir de la cellule (ligne) acutelle (ex.: row = 5, dr = -1 -> newRow = 4 (Vers le haut))
            int newCol = col + dc; // Nouvelle colonne déplacée par dc à partir de la cellule (colonne) acutelle (ex.: row = 7, dr = +1 -> newRow = 8 (Vers la droite))
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) { // Si les coordonnées calculée est bien positioné dans la grille
                if (cells[getIndex(newRow, newCol)]->isAlive()) { // Si la cellule = AliveCell
                    count++; // count = count + 1
                }
            }
        }
    }
    return count; // return 3 s'il y a 3 AliveCell autour de la cellule 
}

// Appliquer la régle
void Grid::applyRules(Rule* rule) {
    // Parcourir tous les cellules de la grille
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            Cell* cell = getCell(row, col); // AliveCell ou DeadCell
            int aliveNeighbors = countAliveNeighbors(row, col); // Calcul le nombre de voisines
            bool nextState = rule->computeNextState(cell, aliveNeighbors); // Définir l'état de cellule (true ou false) de la prochaine génération en appliquant la régle
            cell->setNextState(nextState); // ex) setNextState(false) si le voisin est 1
        }
    }
}

// C'est ici la mise à jour tous les états cellules en même temps
void Grid::update() {
    for (Cell* cell : cells) {
        cell->updateState();
    }
}

void Grid::loadFile(const std::string& path) {
    std::ifstream file(path); // Essayer d'ouvrir le fichier "grid_glider.txt" selon grid->loadFile(inputFile); dans méthode loadGame() dans Game
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier");
    }
    file >> rows >> cols; // Lire la ligne et la colonne (ex.: 20 20)
    if (rows <= 0 || cols <= 0) {
        throw std::runtime_error("Dimensions invalides");
    }

    // Supprimer les cellules existantes (Réinitialiser la grille précédente)
    for (Cell* cell : cells) {
        delete cell;
    }
    cells.clear();

    cells.reserve(rows * cols); // Réserver la capacité dans mémoire à l'avance

    // Lire les cellules
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int state;
            if (!(file >> state)) {
                throw std::runtime_error("Erreur de lecture");
            }
            if (state == 1) { // Si la cellule est 1
                cells.push_back(new AliveCell()); // Changer à AliveCell et enregistrer(push_back) dans la grille
            } else { // Si la cellule est 0
                cells.push_back(new DeadCell()); // Changer à DeadCell et enregistrer(push_back) dans la grille
            }
        }
    }
    file.close();
}

void Grid::saveToFile(const std::string& path) const {
    std::ofstream file(path); // Essayer d'écrire dans le fichier

    // Si le cas d'échec 
    if (!file.is_open()) {
        throw std::runtime_error("Impossible de créer le fichier"); // throw = exception apparaître
    }

    file << rows << " " << cols << "\n"; // Ecrire la ligne et la colonne sur la 1ère ligne du fichier (ex.: 5 5)

    // Parcourir les cellules dans la grille
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Si la cellule est AliveCell = "1" ou DeadCell = "0"
            file << (cells[getIndex(i, j)]->isAlive() ? "1" : "0"); // condition ? "1" : "0" (if-else en une ligne)
            if (j < cols - 1) file << " "; // Espace entre les nombres (ex.: 1 0 0 1)
        }
        file << "\n"; // Saut de la ligne à la fin de chaque ligne 
    }
    file.close();
}

// Comparer
bool Grid::isEqual(const Grid& other) const {
    // Si la ligne et la colonne sont différentes
    if (rows != other.rows || cols != other.cols) {
        return false;
    }

    // Parcourir tous les cellules
    for (int i = 0; i < rows * cols; ++i) {
        // Si la cellule est différent
        if (cells[i]->isAlive() != other.cells[i]->isAlive()) {
            return false;
        }
    }
    return true; // true si tous les cellules sont les mêmes
}

// Deep copy
Grid* Grid::clone() const {
    Grid* newGrid = new Grid(rows, cols);
    for (int i = 0; i < rows * cols; ++i) {
        delete newGrid->cells[i]; // Supprimer d'abord les DeadCell par défaut 
        newGrid->cells[i] = cells[i]->clone(); // Copie colle chaque cellule de la grille acutelle par clone() dans newGrid
    }
    return newGrid;
}