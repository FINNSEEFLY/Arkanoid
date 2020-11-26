//
// Created by FINNSEEFLY on 21.11.2020.
//

#include "Ball.h"

void Ball::CalculateNextPoint(int t) {
    prevOffsetX = offsetX;
    prevOffsetY = offsetY;
    float r = speed * t;
    float h = std::sin(angle)*r;
    float s = std::cos(angle)*r;
    offsetX += s;
    offsetY += h;
    CalculateRECT();
}

Ball::Ball(float &gameZoneX0, float &gameZoneY0, Gdiplus::Image *image, float &scale, float offsetX, float offsetY,
           float speed, float angle) : DrawableShape(gameZoneX0, gameZoneY0, image, scale, offsetX, offsetY),
                                       speed(speed), angle(angle) {}

void Ball::SetOffsetX(float x) {
    SetRepaintRECT();
    offsetX = x;
}

