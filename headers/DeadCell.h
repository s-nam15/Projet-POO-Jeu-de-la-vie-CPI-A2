#ifndef DEADCELL_H
#define DEADCELL_H

#include "Cell.h"

class DeadCell : public Cell {
public:
    DeadCell();
    ~DeadCell() override = default;

    Cell* clone() const override;
};

#endif // DEADCELL_H
