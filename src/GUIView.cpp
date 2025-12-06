#include "GUIView.h"
#include "Game.h"
#include "Grid.h"
#include "Cell.h"
#include <SFML/Graphics.hpp>
#include <iostream>
 
GUIView::GUIView() : View() {}
 
void GUIView::render() {
    if (!game) return;
   
    Grid* grid = game->getGrid();
    if (!grid) return;
   
    // Taille d'une cellule en pixels
    int cellSize = 20;
    int windowWidth = grid->getCols() * cellSize;
    int windowHeight = grid->getRows() * cellSize;
   
    // Créer la fenêtre
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Jeu de la Vie - Conway");
    window.setFramerateLimit(2); // 2 images/seconde pour bien voir
   
    Grid* previousGrid = nullptr;
   
    // Boucle principale
    while (window.isOpen()) {
        // Gestion des événements
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
       
        // Mise à jour de la simulation
        if (!game->isFinished()) {
            // Sauvegarder état précédent
            if (previousGrid) delete previousGrid;
            previousGrid = grid->clone();
           
            // Appliquer règles
            grid->applyRules(game->getRule());
            grid->update();
            game->incrementIteration();
           
            std::cout << "Iteration: " << game->getCurrentIteration() << std::endl;
           
            // Vérifier stabilité
            if (previousGrid && grid->isEqual(*previousGrid)) {
                std::cout << "Grille stabilisee !" << std::endl;
                sf::sleep(sf::seconds(2));
                window.close();
            }
        } else {
            std::cout << "Max iterations" << std::endl;
            sf::sleep(sf::seconds(2));
            window.close();
        }
       
        // Dessiner
        window.clear(sf::Color::White);
       
        sf::RectangleShape cellShape(sf::Vector2f(cellSize - 1, cellSize - 1));
       
        for (int i = 0; i < grid->getRows(); ++i) {
            for (int j = 0; j < grid->getCols(); ++j) {
                Cell* cell = grid->getCell(i, j);
                cellShape.setPosition(j * cellSize, i * cellSize);
               
                if (cell && cell->isAlive()) {
                    cellShape.setFillColor(sf::Color::Black);
                } else {
                    cellShape.setFillColor(sf::Color(220, 220, 220));
                }
               
                window.draw(cellShape);
            }
        }
       
        window.display();
    }
   
    if (previousGrid) delete previousGrid;
}
 