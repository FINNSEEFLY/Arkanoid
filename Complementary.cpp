//
// Created by FINNSEEFLY on 26.11.2020.
//

#include "Complementary.h"

bool IsDotInRect(float x, float y, FloatRECT rect) {
    return x >= rect.left && x <= rect.right && y >= rect.top && y <= rect.bottom;
}

BoolRECT FindOccurrences(FloatRECT target, FloatRECT incoming) {
    BoolRECT result;
    result.leftUp = IsDotInRect(incoming.left, incoming.top, target);
    result.leftDown = IsDotInRect(incoming.left, incoming.bottom, target);
    result.rightUp = IsDotInRect(incoming.right, incoming.top, target);
    result.rightDown = IsDotInRect(incoming.right, incoming.bottom, target);
    return result;
}
