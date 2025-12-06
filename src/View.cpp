#include "View.h"

View::View() : game(nullptr) {}

void View::setGame(Game* g) {
    game = g;
}