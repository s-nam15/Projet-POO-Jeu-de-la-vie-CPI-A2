#include "View.h"

View::View() : game(nullptr) {} // Aucun objet Game n'est encore connecté.

void View::setGame(Game* g) {
    game = g;
}