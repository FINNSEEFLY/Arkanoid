#ifndef ARKANOID_BALL_H
#define ARKANOID_BALL_H


#include "DrawableShape.h"

class Ball : public DrawableShape {
private:
    float speed;
    float angle;
    bool destroyed = false;
public:
    void CalculateNextPoint(int t);

    Ball(float &gameZoneX0, float &gameZoneY0, Gdiplus::Image *&image, float &scale, float offsetX, float offsetY,
         float speed, float angle);

    void SetOffsetX(float x);

    void SetOffsetY(float y);

    void SetOffsetX2(float x);

    void SetOffsetY2(float y);

    [[nodiscard]] float GetAngle() const;

    [[nodiscard]] float GetSpeed() const;

    [[nodiscard]] bool IsDestroyed() const;

    void SetDestroyed();

    void SetAngle(float newAngle);
};


#endif //ARKANOID_BALL_H
