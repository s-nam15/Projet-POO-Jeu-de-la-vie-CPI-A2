#ifndef OBSTACLECELL_H
#define OBSTACLECELL_H

#include "Cell.h"

class ObstacleCell : public Cell {
public:
    ObstacleCell(bool isAlive);
    ~ObstacleCell() override = default;
    
    Cell* clone() const override;
    
    // L'obstacle ne change JAMAIS d'état
    void setNextState(bool state) override;
};

#endif