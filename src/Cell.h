#ifndef CELL_H
#define CELL_H

class Cell {
private:
    bool alive_;
public:
    Cell(bool alive = false) : alive_(alive) {}
    bool isAlive() const { return alive_; }
    void setAlive(bool s) { alive_ = s; }
};

#endif // CELL_H
