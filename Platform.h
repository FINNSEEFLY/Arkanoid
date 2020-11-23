//
// Created by FINNSEEFLY on 19.11.2020.
//

#ifndef ARKANOID_PLATFORM_H
#define ARKANOID_PLATFORM_H


#include "DrawableShape.h"

class Platform : public DrawableShape {
public:
    Platform(float &gameZoneX0, float &gameZoneY0, Gdiplus::Image *image, float &scale, float offsetX, float offsetY);
};


#endif //ARKANOID_PLATFORM_H
