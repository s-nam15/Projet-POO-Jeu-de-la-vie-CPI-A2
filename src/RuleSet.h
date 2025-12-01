#ifndef RULESET_H
#define RULESET_H

#include "Cell.h"

class RuleSet {
public:
    virtual ~RuleSet() = default;
    // Retourne true si la cellule doit être vivante dans la prochaine génération
    virtual bool applyRule(const Cell& cell, int aliveNeighbors) const = 0;
};

#endif // RULESET_H
