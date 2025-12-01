#include "ConsoleRenderer.h"
#include <iostream>

void ConsoleRenderer::render(const Grid& grid) {
    std::cout << grid.toString() << std::endl;
}

void ConsoleRenderer::saveToFile(const Grid& grid, const std::string& path) {
    grid.toFile(path);
}
