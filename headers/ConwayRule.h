#ifndef CONWAYRULE_H
#define CONWAYRULE_H

#include "Rule.h"
#include "Cell.h"

class ConwayRule : public Rule {
public:
    ConwayRule() = default;
    ~ConwayRule() override = default;

    // Implémente les règles classiques du Jeu de la Vie de Conway :
    // - Une cellule morte avec exactement 3 voisins vivants devient vivante
    // - Une cellule vivante avec 2 ou 3 voisins vivants reste vivante
    // - Sinon, la cellule meurt ou reste morte
    bool computeNextState(const Cell* cell, int aliveNeighbors) const override;
};

#endif // CONWAYRULE_H