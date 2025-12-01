#ifndef CONWAYRULE_H
#define CONWAYRULE_H

#include "RuleSet.h"

class ConwayRule : public RuleSet {
public:
    virtual bool applyRule(const Cell& cell, int aliveNeighbors) const override;
};

#endif // CONWAYRULE_H
