//
// Created by FINNSEEFLY on 21.11.2020.
//

#ifndef ARKANOID_BRICK_H
#define ARKANOID_BRICK_H


#include "DrawableShape.h"
#include "Complementary.h"
#include "Ball.h"

#define BRICK_NUM_NULL 0
#define BRICK_NUM_PURPLE 1
#define BRICK_NUM_BLUE 2
#define BRICK_NUM_GREEN 3
#define BRICK_NUM_YELLOW 4
#define BRICK_NUM_RED 5

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

#define BRICK_WIDTH 120
#define BRICK_HEIGHT 50

class Brick : public DrawableShape {
private:
    int hitsBeforeDestruction;
    int price;
    bool isDestroyed = false;
public:
    Brick(float &gameZoneX0, float &gameZoneY0, Gdiplus::Image *image, float &scale, float offsetX, float offsetY,
                 int hitsBeforeDestruction, int experience) : DrawableShape(gameZoneX0, gameZoneY0, image, scale, offsetX,
                                                                            offsetY),
                                                              hitsBeforeDestruction(hitsBeforeDestruction),
                                                              price(experience) {
        CalculateRECT();
    };
    bool IsDestroyed();
    bool HitTheBrick();
    int GetPrice();
};




#endif //ARKANOID_BRICK_H
