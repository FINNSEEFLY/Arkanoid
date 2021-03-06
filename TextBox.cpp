#include "TextBox.h"

std::string TextBox::GetValue() const {
    return value;
}

void TextBox::SetValue(std::string string) {
    TextBox::value = std::move(string);
}

void TextBox::PrepareTextZone() {
    textZone.left = gameBoxX0 + offsetX * scale;
    textZone.right = gameBoxX0 + scale * (offsetX + width);
    textZone.top = gameBoxY0 + offsetY * scale;
    textZone.bottom = gameBoxY0 + scale * (offsetY + height);
}

void TextBox::DrawOnDC(HDC hdc) {
    auto prevValue = SetBkColor(hdc, backgroundColor);
    PrepareTextZone();
    DrawTextA(hdc, value.c_str(), -1, (LPRECT) &textZone, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
    SetBkColor(hdc, prevValue);
}

TextBox::TextBox(float &gameBoxX0, float &gameBoxY0, float &scale, float offsetX, float offsetY, float width,
                 float height, std::string value, COLORREF backgroundColor) : gameBoxX0(gameBoxX0),
                                                                              gameBoxY0(gameBoxY0),
                                                                              scale(scale), offsetX(offsetX),
                                                                              offsetY(offsetY), width(width),
                                                                              height(height),
                                                                              value(std::move(value)),
                                                                              backgroundColor(backgroundColor) {}

