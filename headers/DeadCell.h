#ifndef DEADCELL_H
#define DEADCELL_H

#include "Cell.h"

class DeadCell : public Cell {
public:
    DeadCell();
    ~DeadCell() override = default;

    // // Créer-en une nouvelle en dupliquant DeadCell pour éviter la grille originale change (indépendant)
    Cell* clone() const override;
};

#endif // DEADCELL_H
