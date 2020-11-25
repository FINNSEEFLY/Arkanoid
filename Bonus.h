//
// Created by FINNSEEFLY on 24.11.2020.
//

#ifndef ARKANOID_BONUS_H
#define ARKANOID_BONUS_H


#include "DrawableShape.h"

enum BonusType {
    BONUS_EXPAND,
    BONUS_CUT,
    BONUS_EXPERIENCE_100,
    BONUS_EXPERIENCE_500,
    BONUS_EXPERIENCE_1000,
    BONUS_FIREBALL,
    BONUS_SHOOTING
};

class Bonus : public DrawableShape {
    BonusType bonusType;
};


#endif //ARKANOID_BONUS_H
