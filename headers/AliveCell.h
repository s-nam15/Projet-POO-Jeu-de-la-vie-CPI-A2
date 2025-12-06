
#ifndef ALIVECELL_H
#define ALIVECELL_H

#include "Cell.h"

class AliveCell : public Cell {
public:
    AliveCell();
    ~AliveCell() override = default;

    Cell* clone() const override;
};

#endif // ALIVECELL_H