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

enum BrickType {
    BRICK_TYPE_PURPLE,
    BRICK_TYPE_GREEN,
    BRICK_TYPE_BLUE,
    BRICK_TYPE_RED,
    BRICK_TYPE_YELLOW,
};

class Brick : public DrawableShape {
private:
    int hitsBeforeDestruction;
    int price;
    BrickType brickType;
    bool isDestroyed = false;
public:
    Brick(float &gameZoneX0, float &gameZoneY0, Gdiplus::Image *&image, float &scale, float offsetX, float offsetY,
          int hitsBeforeDestruction, int price, BrickType brickType);

    [[nodiscard]] bool IsDestroyed() const;

    bool HitTheBrick(bool isFireball);

    [[nodiscard]] int GetPrice() const;

    BrickType GetBrickType();
};


#endif //ARKANOID_BRICK_H
