#include "GUIView.h"
#include "Game.h"
#include "ObstacleCell.h"
#include "Grid.h"
#include "Cell.h"
#include "PatternManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>

GUIView::GUIView() : View(), delayMs(500) {} // Vitesse moyenne par défaut

void GUIView::setSpeed(int speed) {
    switch(speed) {
        case 1: delayMs = 1000; break; // Lent
        case 2: delayMs = 500;  break; // Moyen
        case 3: delayMs = 200;  break; // Rapide
        case 5: delayMs = 50;   break; // Très rapide
        default: delayMs = 500; break;
    }
}

int GUIView::getDelayMs() const {
    return delayMs;
}

void GUIView::render() {
    if (!game) return;
    
    Grid* grid = game->getGrid();
    if (!grid) return;
    
    int cellSize = 15;
    int windowWidth = grid->getCols() * cellSize;
    int windowHeight = grid->getRows() * cellSize;
    
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Jeu de la Vie - Conway");
    window.setFramerateLimit(60);
    
    Grid* previousGrid = nullptr;
    
    // Afficher les contrôles
    std::cout << "\n=== CONTROLES ===" << std::endl;
    std::cout << "1 : Vitesse lente" << std::endl;
    std::cout << "2 : Vitesse moyenne" << std::endl;
    std::cout << "3 : Vitesse rapide" << std::endl;
    std::cout << "4 : Vitesse tres rapide" << std::endl;
    std::cout << "ESPACE : Pause/Reprendre" << std::endl;
    std::cout << "G : Placer Glider" << std::endl;
    std::cout << "B : Placer Blinker" << std::endl;
    std::cout << "K : Placer Block" << std::endl;
    std::cout << "T : Placer Toad" << std::endl;
    std::cout << "N : Placer Beacon" << std::endl;
    std::cout << "ECHAP : Quitter\n" << std::endl;
    
    bool paused = false;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed) {
                // Quitter
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                // Contrôle vitesse - touches principales ET pavé numérique
                else if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1) {
                    setSpeed(1);
                    std::cout << "Vitesse: LENTE" << std::endl;
                }
                else if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2) {
                    setSpeed(2);
                    std::cout << "Vitesse: MOYENNE" << std::endl;
                }
                else if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3) {
                    setSpeed(3);
                    std::cout << "Vitesse: RAPIDE" << std::endl;
                }
                else if (event.key.code == sf::Keyboard::Num5 || event.key.code == sf::Keyboard::Numpad5) {
                    setSpeed(5);
                    std::cout << "Vitesse: TRES RAPIDE" << std::endl;
                }
                // Pause
                else if (event.key.code == sf::Keyboard::Space) {
                    paused = !paused;
                    std::cout << (paused ? "PAUSE" : "REPRENDRE") << std::endl;
                }
                // Placement de motifs (au centre de la grille)
                else if (event.key.code == sf::Keyboard::G) {
                    PatternManager::placeGlider(grid, grid->getRows()/2, grid->getCols()/2);
                    std::cout << "Glider place !" << std::endl;
                }
                else if (event.key.code == sf::Keyboard::B) {
                    PatternManager::placeBlinker(grid, grid->getRows()/2, grid->getCols()/2);
                    std::cout << "Blinker place !" << std::endl;
                }
                else if (event.key.code == sf::Keyboard::K) {
                    PatternManager::placeBlock(grid, grid->getRows()/2, grid->getCols()/2);
                    std::cout << "Block place !" << std::endl;
                }
                else if (event.key.code == sf::Keyboard::T) {
                    PatternManager::placeToad(grid, grid->getRows()/2, grid->getCols()/2);
                    std::cout << "Toad place !" << std::endl;
                }
                else if (event.key.code == sf::Keyboard::N) {
                    PatternManager::placeBeacon(grid, grid->getRows()/2, grid->getCols()/2);
                    std::cout << "Beacon place !" << std::endl;
                }
            }
        }
        
        // Mise à jour uniquement si non pausé
        if (!paused && !game->isFinished()) {
            if (previousGrid) delete previousGrid;
            previousGrid = grid->clone();
            
            grid->applyRules(game->getRule());
            grid->update();
            game->incrementIteration();
            
            std::cout << "Iteration: " << game->getCurrentIteration() << std::endl;
            
            // Délai contrôlable
            sf::sleep(sf::milliseconds(delayMs));
            
            if (previousGrid && grid->isEqual(*previousGrid)) {
                std::cout << "Grille stabilisee !" << std::endl;
                sf::sleep(sf::seconds(2));
                window.close();
            }
        } else if (game->isFinished() && !paused) {
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
                
                ObstacleCell* obstacle = dynamic_cast<ObstacleCell*>(cell);
                
                if (obstacle) {
                    // Obstacle - couleur rouge
                    if (obstacle->isAlive()) {
                        cellShape.setFillColor(sf::Color::Green); // Obstacle vivant
                    } else {
                        cellShape.setFillColor(sf::Color::Red); // Obstacle mort (rouge foncé)
                    }
                } else if (cell && cell->isAlive()) {
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