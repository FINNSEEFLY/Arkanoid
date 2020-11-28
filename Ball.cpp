//
// Created by FINNSEEFLY on 21.11.2020.
//

#include "Ball.h"

void Ball::CalculateNextPoint(int t) {
    prevOffsetX = offsetX;
    prevOffsetY = offsetY;
    float r = speed * t;
    float h = std::sin(ConvertDegToRad(angle)) * r;
    float s = std::cos(ConvertDegToRad(angle)) * r;
    SetOffsetX(offsetX + s);
    offsetY += h;
    CalculateRECT();
}



void Ball::SetOffsetX(float x) {
    PrepareToRelocate();
    offsetX = x;
}

float Ball::GetAngle() {
    return angle;
}

void Ball::SetAngle(float angle) {
    this->angle = angle;
}

void Ball::SetOffsetY(float y) {
    PrepareToRelocate();
    offsetY = y;
}

void Ball::SetOffsetX2(float x) {
    PrepareToRelocate();
    offsetX = x - GetWidth();
}

void Ball::SetOffsetY2(float y) {
    PrepareToRelocate();
    offsetY = y - GetHeight();
}



bool Ball::IsDestroyed() {
    return destroyed;
}

void Ball::SetDestroyed() {
    destroyed = true;
}

float Ball::GetSpeed() {
    return speed;
}

Ball::Ball(float &gameZoneX0, float &gameZoneY0, Gdiplus::Image *&image, float &scale, float offsetX, float offsetY,
           float speed, float angle) : DrawableShape(gameZoneX0, gameZoneY0, image, scale, offsetX, offsetY),
                                       speed(speed), angle(angle) {
    CalculateRECT();
}


