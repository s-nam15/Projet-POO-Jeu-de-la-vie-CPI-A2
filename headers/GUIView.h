#ifndef GUIVIEW_H
#define GUIVIEW_H

#include "View.h"

class GUIView : public View {
public:
    GUIView();
    ~GUIView() override = default;
    void render() override;
};

#endif