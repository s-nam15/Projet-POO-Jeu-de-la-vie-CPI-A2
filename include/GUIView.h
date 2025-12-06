#ifndef GUIVIEW_H
#define GUIVIEW_H

#include "View.h"

class GUIView : public View {
private:
    int delayMs;  // Délai en millisecondes

public:
    GUIView();
    ~GUIView() override = default;
    
    void render() override;
    
    // Contrôle de la vitesse
    void setSpeed(int speed); // 1=lent, 2=moyen, 3=rapide
    int getDelayMs() const;
};

#endif