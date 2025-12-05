#ifndef VIEW_H
#define VIEW_H

class Game;

class View {
protected:
    Game* game;

public:
    View();
    virtual ~View() = default;

    // Setter pour associer le jeu à la vue
    void setGame(Game* g);

    // Methode virtuelle pure pour le rendu
    virtual void render() = 0;
};

#endif // VIEW_H