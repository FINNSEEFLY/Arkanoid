//
// Created by FINNSEEFLY on 19.11.2020.
//

#include "Platform.h"
#include "Complementary.h"

Platform::Platform(float &gameZoneX0, float &gameZoneY0, Gdiplus::Image *image, float &scale, float offsetX,
                   float offsetY) : DrawableShape(gameZoneX0, gameZoneY0, image, scale, offsetX, offsetY) {}

void Platform::IncSizeCoefficient() {
    if (sizeCoefficient < 2.24) {
        sizeCoefficient *= 1.5;
    }
}

void Platform::DecSizeCoefficient() {
    if (sizeCoefficient > 0.45) {
        sizeCoefficient /= 1.5;
    }
}

void Platform::PaintOnGraphics(Gdiplus::Graphics &graphics) {
    graphics.DrawImage(image, gameZoneX0 + GetRealOffsetX() * scale, gameZoneY0 + offsetY * scale,
                       GetRealWidth() * scale,
                       this->GetHeight() * scale);
    needRepaint = false;
    SetRepaintRECT();
    wasFilled = false;
}

float Platform::GetRealWidth() {
    return image->GetWidth() * sizeCoefficient;
}

float Platform::GetRealOffsetX() {
    float imageWidth = image->GetWidth();
    return offsetX - (imageWidth * sizeCoefficient - imageWidth) / 2;
}

void Platform::Move(float centerX) {
    if (!IsWasFilled()) {
        SetRepaintRECT();
    }
    float oldOffsetX = offsetX;
    float imageWidth = image->GetWidth();
    float realWidth = GetRealWidth();
    if (((centerX - realWidth / 2 * scale)) < gameZoneX0) {
        offsetX = (imageWidth * sizeCoefficient - imageWidth) / 2;
    } else if ((centerX + realWidth / 2 * scale) > gameZoneX0 + DEFAULT_GAME_ZONE_WIDTH * scale) {
        offsetX = DEFAULT_GAME_ZONE_WIDTH - realWidth + (realWidth - imageWidth) / 2;
    } else {
        offsetX = centerX / scale - gameZoneX0 / scale - imageWidth / 2;
    }
    needRepaint = true;
}

float Platform::GetOffsetY() {
    return offsetY;
}

void Platform::SetRepaintRECT() {
    repaintRect.left = round(gameZoneX0 + GetRealOffsetX() * scale);
    repaintRect.right = ceil(gameZoneX0 + (GetRealOffsetX() + GetRealWidth()) * scale);
    repaintRect.bottom = ceil(gameZoneY0 + (offsetY + GetHeight()) * scale);
    repaintRect.top = round(gameZoneY0 + offsetY * scale);
    wasFilled = true;
}




