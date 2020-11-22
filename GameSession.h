//
// Created by FINNSEEFLY on 22.11.2020.
//

#ifndef ARKANOID_GAMESESSION_H
#define ARKANOID_GAMESESSION_H

#include "Windows.h"
#include "vector"
#include "DrawableShape.h"
#include "gdiplus.h"

class GameSession {
private:
    HWND hWnd;
    RECT clientRect, gameZoneRect;
    HDC hdc, memDC;
    PAINTSTRUCT ps;
    HBITMAP oldbmp, hBM;
    Gdiplus::Graphics *graphics;
    double Scale;
    Gdiplus::Image *backgroundPic;
    Gdiplus::Image *PausePic;
    Gdiplus::Image *gameZonePic;
    Gdiplus::Image *platformPic;
    Gdiplus::Image *ballPic;
    Gdiplus::Image *blueBrickPic;
    Gdiplus::Image *GrinBrickPic;
    Gdiplus::Image *PurpleBrickPic;
    Gdiplus::Image *RedBrickPic;
    Gdiplus::Image *YellowBrickPic;
    std::vector <DrawableShape*> allDrawableObjects;
public:
    GameSession(const HWND hWnd);
    ~GameSession();
    void ResizeEvent();
    void PreparerResize(LPMINMAXINFO &lpminmaxinfo);
    void InitPaint();
    void CompletionPainting();
};


#endif //ARKANOID_GAMESESSION_H
