//
// Created by FINNSEEFLY on 21.11.2020.
//

#include <bits/exception.h>
#include "Brick.h"
#include "Complementary.h"

bool Brick::IsDestroyed() {
    return isDestroyed;
}

/*возвращает:
0 - нет пересечения
1 - слева
2 - слева сверху
3 - сверху
4 - сверху справа
5 - справа
6 - справа снизу
7 - снизу
8 - слева снизу
9 - со всех сторон*/


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

int Brick::GetPrice() {
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


