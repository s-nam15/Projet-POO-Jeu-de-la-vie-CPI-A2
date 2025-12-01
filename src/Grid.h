#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>
#include "Cell.h"
#include "RuleSet.h"

class Grid {
private:
    int rows_;
    int cols_;
    std::vector<Cell> cells_; // stockage ligne-major : r * cols + c

    int index(int r, int c) const { return r * cols_ + c; }

public:
    Grid(int rows = 0, int cols = 0);
    Grid(int rows, int cols, const std::vector<int>& initial); // initial: 0/1 values

    int rows() const { return rows_; }
    int cols() const { return cols_; }
    const Cell& getCell(int r, int c) const;
    Cell& getCell(int r, int c);
    void setCell(int r, int c, bool alive);

    int countAliveNeighbors(int r, int c) const;
    Grid computeNextGrid(const RuleSet& rules) const;

    // I/O utile
    static Grid fromFile(const std::string& path);
    void toFile(const std::string& path) const;
    std::string toString() const;
    bool operator==(const Grid& other) const;
};

#endif // GRID_H
