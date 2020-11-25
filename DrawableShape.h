//
// Created by FINNSEEFLY on 19.11.2020.
//

#ifndef ARKANOID_DRAWABLESHAPE_H
#define ARKANOID_DRAWABLESHAPE_H

#include "windows.h"
#include "gdiplus.h"
#include "Complementary.h"

class DrawableShape {
protected:
    float &gameZoneX0;
    float &gameZoneY0;
    Gdiplus::Image *image;
    float &scale;
    float offsetX;
    float offsetY;
    bool needRepaint = true;
    FloatRECT rect;
public:
    int GetWidth();
    virtual void CalculateRECT();
    int GetHeight();
    FloatRECT GetRECT();
    void SetNeedRepaint();

virtual void PaintOnGraphics(Gdiplus::Graphics &graphics);

DrawableShape(float &gameZoneX0, float &gameZoneY0, Gdiplus::Image *image, float &scale, float offsetX,
                  float offsetY);

};


#endif //ARKANOID_DRAWABLESHAPE_H
