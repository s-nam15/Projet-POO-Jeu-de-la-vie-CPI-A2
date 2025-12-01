#include "Grid.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

Grid::Grid(int rows, int cols) : rows_(rows), cols_(cols), cells_(rows * cols) {}

Grid::Grid(int rows, int cols, const std::vector<int>& initial)
    : rows_(rows), cols_(cols), cells_(rows * cols) {
    if ((int)initial.size() != rows * cols) throw std::runtime_error("Initial size mismatch");
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            cells_[index(r,c)].setAlive(initial[r*cols + c] != 0);
}

const Cell& Grid::getCell(int r, int c) const {
    return cells_.at(index(r,c));
}
Cell& Grid::getCell(int r, int c) {
    return cells_.at(index(r,c));
}
void Grid::setCell(int r, int c, bool alive) {
    cells_.at(index(r,c)).setAlive(alive);
}

int Grid::countAliveNeighbors(int r, int c) const {
    int count = 0;
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;
            int nr = r + dr;
            int nc = c + dc;
            if (nr >= 0 && nr < rows_ && nc >= 0 && nc < cols_) {
                if (getCell(nr, nc).isAlive()) ++count;
            }
        }
    }
    return count;
}

Grid Grid::computeNextGrid(const RuleSet& rules) const {
    Grid next(rows_, cols_);
    for (int r = 0; r < rows_; ++r) {
        for (int c = 0; c < cols_; ++c) {
            const Cell& cur = getCell(r,c);
            int neighbors = countAliveNeighbors(r,c);
            bool nextState = rules.applyRule(cur, neighbors);
            next.setCell(r,c,nextState);
        }
    }
    return next;
}

Grid Grid::fromFile(const std::string& path) {
    std::ifstream in(path);
    if (!in) throw std::runtime_error("Cannot open input file");
    int rows, cols;
    in >> rows >> cols;
    std::vector<int> values;
    values.reserve(rows * cols);
    for (int i = 0; i < rows * cols; ++i) {
        int v; in >> v;
        values.push_back(v);
    }
    return Grid(rows, cols, values);
}

void Grid::toFile(const std::string& path) const {
    std::ofstream out(path);
    out << rows_ << " " << cols_ << "\n";
    for (int r = 0; r < rows_; ++r) {
        for (int c = 0; c < cols_; ++c) {
            out << (getCell(r,c).isAlive() ? 1 : 0);
            if (c+1 < cols_) out << " ";
        }
        out << "\n";
    }
}

std::string Grid::toString() const {
    std::ostringstream oss;
    for (int r = 0; r < rows_; ++r) {
        for (int c = 0; c < cols_; ++c) {
            oss << (getCell(r,c).isAlive() ? 'O' : '.');
        }
        oss << '\n';
    }
    return oss.str();
}

bool Grid::operator==(const Grid& other) const {
    return rows_ == other.rows_ && cols_ == other.cols_ && cells_.size() == other.cells_.size()
           && std::equal(cells_.begin(), cells_.end(), other.cells_.begin(),
                         [](const Cell& a, const Cell& b){ return a.isAlive() == b.isAlive(); });
}
