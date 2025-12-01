#ifndef GAME_H
#define GAME_H

#include "Grid.h"
#include "RuleSet.h"
#include "Renderer.h"
#include <memory>

class Game {
private:
    Grid grid_;
    std::unique_ptr<RuleSet> rules_;
    std::unique_ptr<Renderer> renderer_;
public:
    Game(Grid initial, std::unique_ptr<RuleSet> rules, std::unique_ptr<Renderer> renderer);
    void runConsole(int maxIterations);
    bool isStable() const;
};

#endif // GAME_H
