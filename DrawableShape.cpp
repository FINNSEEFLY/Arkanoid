//
// Created by FINNSEEFLY on 19.11.2020.
//

#include "DrawableShape.h"
#include "iostream"

int DrawableShape::GetHeight() {
    return image->GetHeight();
}

int DrawableShape::GetWidth() {
    return image->GetWidth();
}

void DrawableShape::PaintOnGraphics(Gdiplus::Graphics &graphics) {
    graphics.DrawImage(image, gameZoneX0 + offsetX * scale, gameZoneY0 + offsetY * scale, this->GetWidth() * scale,
                       this->GetHeight() * scale);
    EndPaint();
}


void DrawableShape::EndPaint() {
    needRepaint = false;
    SetRepaintRECT();
    CalculateRECT();
    wasFilled = false;
}


void DrawableShape::CalculateRECT() {
    rect.left = offsetX;
    rect.right = offsetX + image->GetWidth();
    rect.bottom = offsetY + image->GetHeight();
    rect.top = offsetY;
}

void DrawableShape::SetNeedRepaint() {
    needRepaint = true;
}

bool DrawableShape::IsNeedRepaint() {
    return needRepaint;
}

void DrawableShape::SetRepaintRECT() {
    repaintRect.left = round(offsetX * scale + gameZoneX0);
    repaintRect.right = ceil((offsetX + image->GetWidth()) * scale + gameZoneX0);
    repaintRect.bottom = ceil((offsetY + image->GetHeight()) * scale + gameZoneY0);
    repaintRect.top = round(offsetY * scale + gameZoneY0);
    wasFilled = true;
}

bool DrawableShape::IsWasFilled() {
    return wasFilled;
}

FloatRECT DrawableShape::GetRECT() {
    return rect;
}

int DrawableShape::GetNumOfIntersection(FloatRECT TargetRect) {
    BoolRECT occurrences = FindOccurrences(TargetRect, rect);
    int numOfOccurrences = occurrences.leftUp + occurrences.leftDown + occurrences.rightDown + occurrences.rightUp;
    switch (numOfOccurrences) {
        case 0:
            return INTERSECTION_NONE;
        case 1: {
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
            if (occurrences.rightUp) {
                if (rect.right - TargetRect.left > TargetRect.bottom - rect.top) return INTERSECTION_DOWN;
                if (rect.right - TargetRect.left < TargetRect.bottom - rect.top) return INTERSECTION_LEFT;
                return INTERSECTION_LEFT_AND_DOWN;
            }
            throw "case 1";
        }
            break;
        case 2: {
            if (occurrences.rightDown && occurrences.rightUp) return INTERSECTION_LEFT;
            if (occurrences.leftDown && occurrences.rightDown) return INTERSECTION_UP;
            if (occurrences.leftDown && occurrences.leftUp) return INTERSECTION_RIGHT;
            if (occurrences.leftUp && occurrences.rightUp) return INTERSECTION_DOWN;
            throw "case 2";
        }
            break;
        case 3: {
            throw "case 3";
            if (!occurrences.leftUp) return INTERSECTION_LEFT_AND_UP;
            if (!occurrences.rightUp) return INTERSECTION_RIGHT_AND_UP;
            if (!occurrences.rightDown) return INTERSECTION_RIGHT_AND_DOWN;
            if (!occurrences.leftDown) return INTERSECTION_LEFT_AND_DOWN;
            throw new std::exception;
        }
            break;
        case 4: {
            return INTERSECTION_INSIDE;
        }
            break;
        default:
            throw "default";
    }
}

void DrawableShape::PrepareToRelocate() {
    if (!IsWasFilled()) {
        SetRepaintRECT();
    }
    SetNeedRepaint();
}

void DrawableShape::SetOffsetX(float offset) {
    PrepareToRelocate();
    offsetX = offset;
}

void DrawableShape::SetOffsetY(float offset) {
    PrepareToRelocate();
    offsetY = offset;
}

DrawableShape::DrawableShape(float &gameZoneX0, float &gameZoneY0, Gdiplus::Image *&image, float &scale, float offsetX,
                             float offsetY) : gameZoneX0(gameZoneX0), gameZoneY0(gameZoneY0), image(image),
                                              scale(scale), offsetX(offsetX), offsetY(offsetY) {}



