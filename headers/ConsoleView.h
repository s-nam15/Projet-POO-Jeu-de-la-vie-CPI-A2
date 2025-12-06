#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include "View.h"
#include <string>

class ConsoleView : public View {
public:
    ConsoleView();
    ~ConsoleView() override = default;
    void render() override; // Dessiner la grille sur la console
    void printToConsole();
    void saveToFile(int iteration);
};

#endif