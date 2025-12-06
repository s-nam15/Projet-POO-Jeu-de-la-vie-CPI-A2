#ifndef RULE_H
#define RULE_H

class Cell;

class Rule {
public:
    virtual ~Rule() = default;

    // Calcule le prochain état d'une cellule selon les règles
    // cell: la cellule à évaluer
    // aliveNeighbors: nombre de voisins vivants
    // retourne true si la cellule sera vivante, false sinon
    virtual bool computeNextState(const Cell* cell, int aliveNeighbors) const = 0;
};

#endif // RULE_H