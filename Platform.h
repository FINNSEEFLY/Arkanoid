//
// Created by FINNSEEFLY on 19.11.2020.
//

#ifndef ARKANOID_PLATFORM_H
#define ARKANOID_PLATFORM_H


#include "DrawableShape.h"

class Platform : public DrawableShape {
private:
    float sizeCoefficient = 1;
public:
    void IncSizeCoefficient();
    void DecSizeCoefficient();
    void Move(float centerX);
    float GetRealWidth();
    float GetRealOffsetX();
    float GetOffsetY();
    Platform(float &gameZoneX0, float &gameZoneY0, Gdiplus::Image *image, float &scale, float offsetX, float offsetY);
    void PaintOnGraphics(Gdiplus::Graphics &graphics) override;
    void SetRepaintRECT() override;
    void CalculateRECT() override;
};


#endif //ARKANOID_PLATFORM_H
