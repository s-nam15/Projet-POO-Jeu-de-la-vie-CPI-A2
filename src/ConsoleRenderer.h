// ConsoleRenderer.h
#pragma once
#include "Renderer.h"

class ConsoleRenderer : public Renderer {
public:
    void render(const Grid& grid) override;
    void saveToFile(const Grid& grid, const std::string& path) override;
};
