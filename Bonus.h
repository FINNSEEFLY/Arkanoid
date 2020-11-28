//
// Created by FINNSEEFLY on 24.11.2020.
//

#ifndef ARKANOID_BONUS_H
#define ARKANOID_BONUS_H


#include "DrawableShape.h"

/*Вероятности выпадения:
 * В принципе бонус - 1/3
 * Конкретный бонус(дополнительно к предыдущему)
 * Expand - */
enum BonusType {
    BONUS_NONE,
    BONUS_EXPAND,
    BONUS_CUT,
    BONUS_EXPERIENCE,
    BONUS_FIREBALL,
    BONUS_MORE_BALLS
};
#define BRICK_HITS_PURPLE 1
#define BRICK_HITS_BLUE 1
#define BRICK_HITS_GREEN 1
#define BRICK_HITS_YELLOW 2
#define BRICK_HITS_RED 3

#define BRICK_PRICE_PURPLE 10
#define BRICK_PRICE_BLUE 15
#define BRICK_PRICE_GREEN 20
#define BRICK_PRICE_YELLOW 25
#define BRICK_PRICE_RED 30

#define DEFAULT_BONUS_SPEED 0.2


class Bonus : public DrawableShape {
private:
    BonusType bonusType;
    int price = 0;
    bool destroyed = false;
    void PrepareToRelocate();
public:
    bool IsDestroyed();
    void SetDestroyed();
    void CalculateNextPoint(int t);
    BonusType GetBonusType();
    int GetPrice();

    Bonus(float &gameZoneX0, float &gameZoneY0, Gdiplus::Image *image, float &scale, float offsetX, float offsetY,
          BonusType bonusType, int price);
};


#endif //ARKANOID_BONUS_H
