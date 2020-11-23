//
// Created by FINNSEEFLY on 19.11.2020.
//

#include "Platform.h"

Platform::Platform(float &gameZoneX0, float &gameZoneY0, Gdiplus::Image *image, float &scale, float offsetX,
                   float offsetY) : DrawableShape(gameZoneX0, gameZoneY0, image, scale, offsetX, offsetY) {}
