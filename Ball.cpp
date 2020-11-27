//
// Created by FINNSEEFLY on 21.11.2020.
//

#include "Ball.h"

void Ball::CalculateNextPoint(int t) {
    prevOffsetX = offsetX;
    prevOffsetY = offsetY;
    float r = speed * t;
    float h = std::sin(ConvertDegToRad(angle)) * r;
    float s = std::cos(ConvertDegToRad(angle)) * r;
    SetOffsetX(offsetX+s);
    offsetY += h;
    CalculateRECT();
}

Ball::Ball(float &gameZoneX0, float &gameZoneY0, Gdiplus::Image *image, float &scale, float offsetX, float offsetY,
           float speed, float angle) : DrawableShape(gameZoneX0, gameZoneY0, image, scale, offsetX, offsetY),
                                       speed(speed), angle(angle) {}

void Ball::SetOffsetX(float x) {
    PrepareToRelocate();
    offsetX = x;
}

float Ball::GetAngle() {
    return angle;
}

void Ball::SetAngle(float angle) {
    this->angle = angle;
}

void Ball::SetOffsetY(float y) {
    PrepareToRelocate();
    offsetY = y;
}

void Ball::PrepareToRelocate() {
    if (!IsWasFilled()) {
        SetRepaintRECT();
    }
    SetNeedRepaint();
}

void Ball::SetOffsetX2(float x) {
    PrepareToRelocate();
    offsetX=x-GetWidth();
}

void Ball::SetOffsetY2(float y) {
    PrepareToRelocate();
    offsetY=y-GetHeight();
}

int Ball::GetNumOfIntersection(FloatRECT TargetRect) {
    BoolRECT occurrences = FindOccurrences(TargetRect, rect);
    int numOfOccurrences = occurrences.leftUp+occurrences.leftDown+occurrences.rightDown+occurrences.rightUp;
    switch (numOfOccurrences) {
        case 0:
            return INTERSECTION_NONE;
        case 1:
        {
            if (occurrences.rightDown) {
                if (rect.bottom - TargetRect.top < rect.right - TargetRect.left) return INTERSECTION_UP;
                if (rect.bottom - TargetRect.top > rect.right - TargetRect.left) return INTERSECTION_LEFT;
                return INTERSECTION_LEFT_AND_UP;
            }
            if (occurrences.leftDown) {
                if (rect.bottom - TargetRect.top < TargetRect.right - rect.left) return INTERSECTION_UP;
                if (rect.bottom - TargetRect.top > TargetRect.right - rect.left) return INTERSECTION_RIGHT;
                return INTERSECTION_RIGHT_AND_UP;
            }
            if (occurrences.leftUp) {
                if (TargetRect.right - rect.left < TargetRect.bottom - rect.top) return INTERSECTION_RIGHT;
                if (TargetRect.right - rect.left > TargetRect.bottom - rect.top) return INTERSECTION_DOWN;
                return INTERSECTION_RIGHT_AND_DOWN;
            }
            if (occurrences.rightUp)  {
                if (rect.right - TargetRect.left > TargetRect.bottom - rect.top) return INTERSECTION_DOWN;
                if (rect.right - TargetRect.left < TargetRect.bottom - rect.top) return INTERSECTION_LEFT;
                return INTERSECTION_LEFT_AND_DOWN;
            }
            throw new std::exception;
        } break;
        case 2: {
            if (occurrences.rightDown&&occurrences.rightUp) return INTERSECTION_LEFT;
            if (occurrences.leftDown&&occurrences.rightDown) return INTERSECTION_UP;
            if (occurrences.leftDown&&occurrences.leftUp) return INTERSECTION_RIGHT;
            if (occurrences.leftUp&&occurrences.rightUp) return INTERSECTION_DOWN;
            throw new std::exception;
        } break;
        case 3: {
            throw new std::exception;
            if (!occurrences.leftUp) return INTERSECTION_LEFT_AND_UP;
            if (!occurrences.rightUp) return INTERSECTION_RIGHT_AND_UP;
            if (!occurrences.rightDown) return INTERSECTION_RIGHT_AND_DOWN;
            if (!occurrences.leftDown) return INTERSECTION_LEFT_AND_DOWN;
            throw new std::exception;
        } break;
        case 4: {
            return INTERSECTION_INSIDE;
        } break;
        default:
            throw new std::exception();
    }
}

bool Ball::IsDestroyed() {
    return destroyed;
}

void Ball::SetDestroyed() {
    destroyed=true;
}


