//
// Created by FINNSEEFLY on 21.11.2020.
//

#ifndef ARKANOID_BALL_H
#define ARKANOID_BALL_H


#include "DrawableShape.h"

class Ball : DrawableShape {
private:
    float speed;
    float angle;
    float prevOffsetX;
    float prevOffsetY;
};


#endif //ARKANOID_BALL_H
