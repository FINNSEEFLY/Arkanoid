//
// Created by FINNSEEFLY on 22.11.2020.
//

#ifndef ARKANOID_GAMESESSION_H
#define ARKANOID_GAMESESSION_H

#include "Windows.h"
#include "vector"
#include "DrawableShape.h"
#include "gdiplus.h"
#include "Ball.h"
#include "Brick.h"
#include "Platform.h"


class GameSession {
private:
    HWND hWnd;
    HDC hdc, memDC;
    PAINTSTRUCT ps;
    HBITMAP oldbmp, hBM;
    RECT clientRect;
/*    RECT zeroRect;*/

    float clientWidth, clientHeight;
    float scale;

    float backgroundX0;
    float backgroundY0;
    float backgroundWidth;
    float backgroundHeight;

    float gameBoxX0;
    float gameBoxY0;
    float gameBoxSide;

    float gameZoneX0;
    float gameZoneY0;

    LOGFONT lf;

    RECT levelTextRect;
    RECT scoreTextRect;
    RECT livesTextRect;

    int level;
    int score;
    int lives;

    Gdiplus::Graphics *graphics;

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
    std::vector <Ball*> balls;
    std::vector <Brick*> bricks;
    Platform* platform;

    HFONT hFont;

    bool isGameStarted = false;
    bool isGamePaused;

    void CalculateBackground(float &backgroundX0, float &backgroundY0, float &backgroundWidth, float &backgroundHeight);
    void CalculateGameBox(float &gameBoxX0, float &gameBoxY0, float &gameBoxSide, float &scale);
    void CalculateGameZone();
    LPCSTR ConvertIntToStr(int value);
    void CompletionPaintingBEP();
    void InitPaintBEP();
    void CompletionPaintingGRP();
    void InitPaintGRP();
    void CalculateFontProperties();
    void PrepareFontDrawing(HFONT &hfont);
    void CompletionFontDrawing(HFONT &hfont);
    void BlockFactory();
public:
    GameSession(const HWND hWnd);
    ~GameSession();
    void ResizeEvent();
    void PreparerResize(LPMINMAXINFO &lpminmaxinfo);
    void Repaint();
};


#endif //ARKANOID_GAMESESSION_H
