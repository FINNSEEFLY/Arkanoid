#ifndef ARKANOID_BONUS_H
#define ARKANOID_BONUS_H


#include "DrawableShape.h"

enum BonusType {
    BONUS_NONE,
    BONUS_EXPAND,
    BONUS_CUT,
    BONUS_EXPERIENCE,
    BONUS_FIREBALL,
    BONUS_MORE_BALLS
};

#define DEFAULT_BONUS_SPEED 0.2


class Bonus : public DrawableShape {
private:
    BonusType bonusType;
    int price = 0;
    bool destroyed = false;
public:
    bool IsDestroyed();

    void SetDestroyed();

    void CalculateNextPoint(int t);

    BonusType GetBonusType();

    int GetPrice();

    Bonus(float &gameZoneX0, float &gameZoneY0, Gdiplus::Image *&image, float &scale, float offsetX, float offsetY,
          BonusType bonusType, int price);
};


#endif //ARKANOID_BONUS_H
