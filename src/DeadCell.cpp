#include "DeadCell.h"

DeadCell::DeadCell() : Cell(false) {}

Cell* DeadCell::clone() const {
    return new DeadCell(*this);
}