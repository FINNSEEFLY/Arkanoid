//
// Created by FINNSEEFLY on 26.11.2020.
//

#include "Complementary.h"
#include "math.h"

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
LPCSTR ConvertIntToLPCSTR(int value) {
    std::stringstream s;
    s << std::scientific << value;
    return s.str().c_str();
}

std::string ConvertIntToString(int value) {
    std::stringstream s;
    s << std::scientific << value;
    return s.str();
}

float ConvertDegToRad(float value) {
    return value * M_PI / 180;
}
