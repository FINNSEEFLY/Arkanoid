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
int Brick::GetNumOfIntersection(Ball ball) {
    BoolRECT occurrences = FindOccurrences(rect, ball.GetRECT());
    int numOfOccurrences = occurrences.leftUp+occurrences.leftDown+occurrences.rightDown+occurrences.leftUp+occurrences.rightUp;
    switch (numOfOccurrences) {
        case 1:
        {
            if (occurrences.rightDown) return 2;
            if (occurrences.leftDown) return 4;
            if (occurrences.leftUp) return 6;
            if (occurrences.rightUp) return 8;
            throw new std::exception;
        } break;
        case 2: {
            if (occurrences.rightDown&&occurrences.rightUp) return 1;
            if (occurrences.leftDown&&occurrences.rightDown) return 3;
            if (occurrences.leftDown&&occurrences.leftUp) return 5;
            if (occurrences.leftUp&&occurrences.rightUp) return 7;
            throw new std::exception;
        } break;
        case 3: {
            if (!occurrences.leftUp) return 2;
            if (!occurrences.rightUp) return 4;
            if (!occurrences.rightDown) return 6;
            if (!occurrences.leftDown) return 8;
            throw new std::exception;
        } break;
        case 4: {
            return 9;
        } break;
        default:
            throw new std::exception();
    }
}
