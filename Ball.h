//
// Created by FINNSEEFLY on 21.11.2020.
//

#ifndef ARKANOID_BALL_H
#define ARKANOID_BALL_H


#include "DrawableShape.h"

class Ball : public DrawableShape {
private:
    float speed;
    float angle;
    float prevOffsetX;
    float prevOffsetY;
public:
    void CalculateNextPoint(int t);

    Ball(float &gameZoneX0, float &gameZoneY0, Gdiplus::Image *image, float &scale, float offsetX, float offsetY,
         float speed, float angle);
};


#endif //ARKANOID_BALL_H
