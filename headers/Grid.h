#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>
#include "Cell.h"
#include "Rule.h"

class Grid {
private:
    int rows;
    int cols;
    std::vector<Cell*> cells;
    int getIndex(int row, int col) const;

public:
    Grid();
    Grid(int rows, int cols);
    ~Grid();
    int getRows() const;
    int getCols() const;
    Cell* getCell(int row, int col) const;
    int countAliveNeighbors(int row, int col) const;
    void applyRules(Rule* rule);
    void update();
    void loadFile(const std::string& path);
    void saveToFile(const std::string& path) const;
    bool isEqual(const Grid& other) const;
    Grid* clone() const;
};

#endif