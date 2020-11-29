#include "Brick.h"

bool Brick::IsDestroyed() const {
    return isDestroyed;
}

bool Brick::HitTheBrick(bool isFireball) {
    hitsBeforeDestruction--;
    if (hitsBeforeDestruction == 0 || isFireball) {
        isDestroyed = true;
        wasFilled = true;
        needRepaint = false;
        return true;
    }
    return false;
}

int Brick::GetPrice() const {
    return price;
}

BrickType Brick::GetBrickType() {
    return brickType;
}

Brick::Brick(float &gameZoneX0, float &gameZoneY0, Gdiplus::Image *&image, float &scale, float offsetX, float offsetY,
             int hitsBeforeDestruction, int price, BrickType brickType) : DrawableShape(gameZoneX0, gameZoneY0, image,
                                                                                        scale, offsetX, offsetY),
                                                                          hitsBeforeDestruction(hitsBeforeDestruction),
                                                                          price(price), brickType(brickType) {
    CalculateRECT();
}


