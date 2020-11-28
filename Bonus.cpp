//
// Created by FINNSEEFLY on 24.11.2020.
//

#include "Bonus.h"

bool Bonus::IsDestroyed() {
    return destroyed;
}

void Bonus::SetDestroyed() {
    destroyed = true;
}

Bonus::Bonus(float &gameZoneX0, float &gameZoneY0, Gdiplus::Image *image, float &scale, float offsetX, float offsetY,
             BonusType bonusType, int price) : DrawableShape(gameZoneX0, gameZoneY0, image, scale, offsetX, offsetY),
                                               bonusType(bonusType), price(price) {}

void Bonus::CalculateNextPoint(int t) {
    PrepareToRelocate();
    offsetY += DEFAULT_BONUS_SPEED*t;
    CalculateRECT();
}

void Bonus::PrepareToRelocate() {
    if (!IsWasFilled()) {
        SetRepaintRECT();
    }
    SetNeedRepaint();
}

BonusType Bonus::GetBonusType() {
    return bonusType;
}

int Bonus::GetPrice() {
    return price;
}
