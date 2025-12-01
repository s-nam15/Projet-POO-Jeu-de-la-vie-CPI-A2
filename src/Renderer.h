#pragma once
#include "Grid.h"
#include <string>

class Renderer {
public:
    virtual ~Renderer() = default;
    virtual void render(const Grid& grid) = 0;

    // Ajout pour les sorties fichiers
    virtual void saveToFile(const Grid& grid, const std::string& path) {
        // Par défaut, ne fait rien (pour SFML)
    }
};
