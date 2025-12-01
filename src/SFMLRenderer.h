#ifndef SFMLRENDERER_H
#define SFMLRENDERER_H

#include "Renderer.h"

#ifdef USE_SFML
// si USE_SFML défini, inclure SFML
#include <SFML/Graphics.hpp>
#endif

class SFMLRenderer : public Renderer {
public:
    SFMLRenderer(int cellSize = 10);
    virtual void render(const Grid& grid) override;
private:
    int cellSize_;
};

#endif // SFMLRENDERER_H
