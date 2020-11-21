//
// Created by FINNSEEFLY on 21.11.2020.
//

#ifndef ARKANOID_BRICK_H
#define ARKANOID_BRICK_H


#include "cmake-build-debug/DrawableShape.h"
#include "Resources.h"
class Brick : public DrawableShape {
private:
    BonusType bonusType;
    int Resistance;
    int Experience;
};


#endif //ARKANOID_BRICK_H
