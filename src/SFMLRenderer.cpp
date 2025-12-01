#include "SFMLRenderer.h"
#include <iostream>

SFMLRenderer::SFMLRenderer(int cellSize) : cellSize_(cellSize) {}

void SFMLRenderer::render(const Grid& grid) {
#ifdef USE_SFML
    // Implémentation réelle ici (requiert SFML installé et linking)
    // Exemple: créer sf::RenderWindow, dessiner rectangles pour chaque cellule vivante.
    std::cout << "[SFMLRenderer] rendering (SFML enabled)\n";
#else
    // Stub convivial si SFML absent
    std::cout << "[SFMLRenderer] SFML non activé. Utilisez ConsoleRenderer ou compilez avec -DUSE_SFML.\n";
#endif
}
