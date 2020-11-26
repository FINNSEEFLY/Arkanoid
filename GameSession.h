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
#include "Bonus.h"


class GameSession {
private:
    HWND hWnd;
    HDC hdc, memDC;
    PAINTSTRUCT ps;
    HBITMAP oldBmp, hBM;
    HBRUSH brush;
    RECT clientRect;

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
    Gdiplus::Image *pausePic;
    Gdiplus::Image *gameZonePic;
    Gdiplus::Image *platformPic;
    Gdiplus::Image *ballPic;
    Gdiplus::Image *blueBrickPic;
    Gdiplus::Image *greenBrickPic;
    Gdiplus::Image *purpleBrickPic;
    Gdiplus::Image *redBrickPic;
    Gdiplus::Image *yellowBrickPic;

    std::vector <Ball*> balls;
    std::vector <Brick*> bricks;
    std::vector <Bonus*> bonuses;
    Platform* platform;

    HFONT hFont;

    bool isGameStarted = false;
    bool isGamePaused = false;
    bool isNeedGeneration = true;
    bool isWaitForStarted = false;
    bool isNeedRepaintBackground = true;

    bool resized = false;

    DWORD StartTick;
    DWORD EndTick;

    bool GenerateBricks(int numOfLevel);
    Brick* BrickFactory(int brickPosX, int brickPosY, int brickType);
    void CalculateBackground(float &backgroundX0, float &backgroundY0, float &backgroundWidth, float &backgroundHeight);
    void CalculateGameBox(float &gameBoxX0, float &gameBoxY0, float &gameBoxSide, float &scale);
    void CalculateGameZone();
    static LPCSTR ConvertIntToLPWSTR(int value);
    static std::string ConvertIntToString(int value);
    void CompletionPaintingBEP();
    void InitPaintBEP();
    void CompletionPaintingGRP();
    void InitPaintGRP();
    void CalculateFontProperties();
    void PrepareFontDrawing(HFONT &hfont);
    void CompletionFontDrawing(HFONT &hfont);
    void RepaintController();
    void DeleteBalls();
    void DeleteBricks();
    void DeleteBonuses();
    void SetAllNeedRepaint(bool background);
    void RepaintWhatsNeeded();
public:

    void SetResized();
    GameSession(const HWND hWnd);
    ~GameSession();
    void ResizeEvent();
    void PreparerResize(LPMINMAXINFO &lpminmaxinfo);
    void Repaint();
    void MovePlatform(float center);
    void SwitchPause();
    bool IsPaused();
    void TryToStartGame();
};


#endif //ARKANOID_GAMESESSION_H
