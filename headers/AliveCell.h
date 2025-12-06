
#ifndef ALIVECELL_H
#define ALIVECELL_H

#include "Cell.h"

class AliveCell : public Cell {
public:
    AliveCell();
    ~AliveCell() override = default;

    // Créer-en une nouvelle en dupliquant AliveCell pour éviter la grille originale change (indépendant)
    Cell* clone() const override;
};

#endif // ALIVECELL_H