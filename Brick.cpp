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


bool Brick::HitTheBrick() {
    hitsBeforeDestruction--;
    if (hitsBeforeDestruction == 0) {
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
