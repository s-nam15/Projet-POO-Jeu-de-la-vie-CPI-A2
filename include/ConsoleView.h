#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include "View.h"
#include <string>

class ConsoleView : public View {
public:

// Constructeur par défaut : Initialise l'objet ConsoleView.
    ConsoleView();

// Destructeur : Libère les ressources si nécessaire. 
// 'override' assure que la méthode surcharge correctement le destructeur virtuel de 'View'.
    ~ConsoleView() override = default;

// Méthode de rendu principale : Surcharge la méthode pure virtuelle de la classe de base 'View'.
// Dans le cas de la console, cette méthode pourrait orchestrer la simulation et l'affichage.
    void render() override;

// Méthode spécifique à la console : Affiche l'état actuel de la grille 
// dans la fenêtre de la console/terminal (stdout).
    void printToConsole();

// Méthode spécifique pour la console : Enregistre l'état actuel de la grille
    void saveToFile(int iteration);
};

#endif