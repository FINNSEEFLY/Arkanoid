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
    needRepaint = false;
    SetRepaintRECT();
    wasFilled = false;
}

DrawableShape::DrawableShape(float &gameZoneX0, float &gameZoneY0, Gdiplus::Image *image, float &scale, float offsetX,
                             float offsetY) : gameZoneX0(gameZoneX0), gameZoneY0(gameZoneY0), image(image),
                                              scale(scale), offsetX(offsetX), offsetY(offsetY) {}

FloatRECT DrawableShape::GetRECT() {
    return rect;
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

