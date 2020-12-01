#include "Ball.h"

void Ball::CalculateNextPoint(int t) {
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

float Ball::GetAngle() const {
    return angle;
}

void Ball::SetAngle(float newAngle) {
    this->angle = newAngle;
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

bool Ball::IsDestroyed() const {
    return destroyed;
}

void Ball::SetDestroyed() {
    destroyed = true;
}

float Ball::GetSpeed() const {
    return speed;
}

Ball::Ball(float &gameZoneX0, float &gameZoneY0, Gdiplus::Image *&image, float &scale, float offsetX, float offsetY,
           float speed, float angle) : DrawableShape(gameZoneX0, gameZoneY0, image, scale, offsetX, offsetY),
                                       speed(speed), angle(angle) {
    CalculateRECT();
}


