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

    [[nodiscard]] std::string GetValue() const;

    void SetValue(std::string string);

    void DrawOnDC(HDC hdc);
};


#endif //ARKANOID_TEXTBOX_H
