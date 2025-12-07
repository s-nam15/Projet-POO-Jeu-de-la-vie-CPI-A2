#include <iostream>
#include <string>
#include "Game.h"

// Affiche un message expliquant à l'utilisateur comment exécuter le programme.
void printUsage(const char* programName) {
    std::cout << "Usage: " << programName << " <fichier> <mode> <iterations>" << std::endl;
    std::cout << "  <fichier>     : Chemin vers le fichier" << std::endl;
    std::cout << "  <mode>        : 0 = console, 1 = graphique" << std::endl;
    std::cout << "  <iterations>  : Nombre max" << std::endl;
}

int main(int argc, char* argv[]) {
    // Vérification du nombre d'arguments
    // 'argc' (argument count) doit être 4 
    if (argc != 4) {
        std::cerr << "Erreur arguments" << std::endl;
        printUsage(argv[0]); // Affiche l'aide
        return 1; // Termine le programme avec un code d'erreur
    }

    // --- 1. Lecture et conversion des arguments ---
    
    // argv[1] est le chemin du fichier d'entrée (string)
    std::string inputFile = argv[1]; 
    
    // argv[2] est le mode (doit être converti en int)
    int mode = std::stoi(argv[2]); 
    
    // argv[3] est le nombre d'itérations max (doit être converti en int)
    int iterations = std::stoi(argv[3]);

    // --- 2. Validation des arguments ---

    // Validation du mode (doit être 0 ou 1)
    if (mode != 0 && mode != 1) {
        std::cerr << "Mode doit etre 0 ou 1" << std::endl;
        return 1;
    }

    // Validation du nombre d'itérations (doit être strictement positif)
    if (iterations <= 0) {
        std::cerr << "Iterations > 0" << std::endl;
        return 1;
    }

    // --- 3. Initialisation et Lancement du Jeu ---

    try {
        // Création de l'objet Game (Contrôleur) avec les paramètres lus.
        Game game(iterations, mode, inputFile); 
        
        // Chargement initial de la grille à partir du fichier (peut lever une exception en cas d'erreur de lecture)
        game.loadGame(); 
        
        // Lance la simulation (ceci appellera runConsole ou runGraphic selon le 'mode')
        game.run(); 
    } catch (const std::exception& e) {
        // Interception de toute exception levée durant le chargement ou l'exécution (ex: fichier non trouvé, format invalide)
        std::cerr << "Erreur: " << e.what() << std::endl;
        return 1; // Termine le programme suite à une erreur
    }

    return 0; // Termine le programme avec succès
}