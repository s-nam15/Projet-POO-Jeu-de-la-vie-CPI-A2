#include "Grid.h"
#include "AliveCell.h"
#include "DeadCell.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

Grid::Grid() : rows(0), cols(0) {}

Grid::Grid(int rows, int cols) : rows(rows), cols(cols) {
    cells.reserve(rows * cols);
    for (int i = 0; i < rows * cols; ++i) {
        cells.push_back(new DeadCell());
    }
}

Grid::~Grid() {
    for (Cell* cell : cells) {
        delete cell;
    }
    cells.clear();
}

int Grid::getIndex(int row, int col) const {
    return row * cols + col;
}

int Grid::getRows() const {
    return rows;
}

int Grid::getCols() const {
    return cols;
}

Cell* Grid::getCell(int row, int col) const {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return nullptr;
    }
    return cells[getIndex(row, col)];
}

int Grid::countAliveNeighbors(int row, int col) const {
    int count = 0;
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;
            int newRow = row + dr;
            int newCol = col + dc;
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
                if (cells[getIndex(newRow, newCol)]->isAlive()) {
                    count++;
                }
            }
        }
    }
    return count;
}

void Grid::applyRules(Rule* rule) {
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            Cell* cell = getCell(row, col);
            int aliveNeighbors = countAliveNeighbors(row, col);
            bool nextState = rule->computeNextState(cell, aliveNeighbors);
            cell->setNextState(nextState);
        }
    }
}

void Grid::update() {
    for (Cell* cell : cells) {
        cell->updateState();
    }
}

void Grid::loadFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier");
    }
    file >> rows >> cols;
    if (rows <= 0 || cols <= 0) {
        throw std::runtime_error("Dimensions invalides");
    }
    for (Cell* cell : cells) {
        delete cell;
    }
    cells.clear();
    cells.reserve(rows * cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int state;
            if (!(file >> state)) {
                throw std::runtime_error("Erreur de lecture");
            }
            if (state == 1) {
                cells.push_back(new AliveCell());
            } else {
                cells.push_back(new DeadCell());
            }
        }
    }
    file.close();
}

void Grid::saveToFile(const std::string& path) const {
    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible de creer le fichier");
    }
    file << rows << " " << cols << "\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file << (cells[getIndex(i, j)]->isAlive() ? "1" : "0");
            if (j < cols - 1) file << " ";
        }
        file << "\n";
    }
    file.close();
}

bool Grid::isEqual(const Grid& other) const {
    if (rows != other.rows || cols != other.cols) {
        return false;
    }
    for (int i = 0; i < rows * cols; ++i) {
        if (cells[i]->isAlive() != other.cells[i]->isAlive()) {
            return false;
        }
    }
    return true;
}

Grid* Grid::clone() const {
    Grid* newGrid = new Grid(rows, cols);
    for (int i = 0; i < rows * cols; ++i) {
        delete newGrid->cells[i];
        newGrid->cells[i] = cells[i]->clone();
    }
    return newGrid;
}