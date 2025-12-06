#ifndef CELL_H
#define CELL_H

class Cell {
protected:
    bool alive; // Etat actuel (true = vivant, false = mort)
    bool nextState; /*Sauvegarder l'état de la prochaine génération 
                    (Si on change attribut <<alive>> direct, ça affecte le calcul d'autres cellules qui n'ont pas encore été calculées. 
                    C'est pour ça il faut précalculer et stocker l'état de la génération suivante dans nextState et 
                    lorsque tous les calculs cellulaires sont terminés, tous en même temps alive = nextState -> Toute une génération est mise à jour simultanément)
                    */
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

    // Fonction virtuelle pure qui clone un objet Cell (polymorphisme)
    virtual Cell* clone() const = 0;
};

#endif // CELL_H