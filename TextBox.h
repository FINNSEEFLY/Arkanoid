//
// Created by FINNSEEFLY on 29.11.2020.
//

#ifndef ARKANOID_TEXTBOX_H
#define ARKANOID_TEXTBOX_H

#include <string>
#include "Windows.h"

class TextBox {
private:
    float &gameBoxX0;
    float &gameBoxY0;
    float &scale;
    float offsetX;
    float offsetY;
    float width;
    float height;
    RECT textZone;
    std::string value;
    COLORREF backgroundColor;

    void PrepareTextZone();

public:

    TextBox(float &gameBoxX0, float &gameBoxY0, float &scale, float offsetX, float offsetY, float width, float height,
            std::string value, COLORREF backgroundColor);

    const RECT &getTextZone() const;

    std::string getValue() const;

    void setValue(std::string value);

    void DrawOnDC(HDC hdc);
};


#endif //ARKANOID_TEXTBOX_H
