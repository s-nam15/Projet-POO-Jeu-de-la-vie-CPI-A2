#ifndef CELL_H
#define CELL_H

class Cell {
protected:
    bool alive;
    bool nextState;

public:
    Cell(bool isAlive);
    virtual ~Cell() = default;

    // Getters
    virtual bool isAlive() const;
    bool getNextState() const;

    // Setters
    void setNextState(bool state);
    
    // Met à jour l'état actuel avec le prochain état calculé
    void updateState();

    // Méthode virtuelle pure pour le polymorphisme
    virtual Cell* clone() const = 0;
};

#endif // CELL_H