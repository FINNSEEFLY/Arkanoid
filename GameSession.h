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
    RECT windowRect;
    RECT prevWindowRect;

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

    int level, oldLevel;
    int score, oldScore;
    int lives, oldLives;


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

    Gdiplus::Image *fireBallPic;
    Gdiplus::Image *bonusBallPic;
    Gdiplus::Image *bonusCutPic;
    Gdiplus::Image *bonusExpandPic;
    Gdiplus::Image *bonusFireBallPic;
    Gdiplus::Image *bonusEXP1Pic;
    Gdiplus::Image *bonusEXP2Pic;
    Gdiplus::Image *bonusEXP3Pic;
    Gdiplus::Image *bonusEXP4Pic;
    Gdiplus::Image *bonusEXP5Pic;

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
    bool isNeedRepaintLevel = true;
    bool isNeedRepaintScore = true;
    bool isNeedRepaintLives = true;

    bool isFireBall = false;

    DWORD startTick;
    DWORD endTick;

    int numOfBricks;
    int numOfBalls;
    FloatRECT leftSide;
    FloatRECT rightSide;
    FloatRECT upSide;
    FloatRECT downSide;



    int GenerateBricks(int numOfLevel);
    Brick* BrickFactory(int brickPosX, int brickPosY, int brickType);
    Bonus* BonusFactory(float offsetX, float offsetY, BonusType bonusType, BrickType brickType);
    void CalculateBackground(float &backgroundX0, float &backgroundY0, float &backgroundWidth, float &backgroundHeight);
    void CalculateGameBox(float &gameBoxX0, float &gameBoxY0, float &gameBoxSide, float &scale);
    void CalculateGameZone();
    void CompletionPaintingBEP();
    void InitPaintBEP();
    void CalculateFontProperties();
    void PrepareFontDrawing(HFONT &hfont);
    void CompletionFontDrawing(HFONT &hfont);
    void RepaintController();
    void DeleteBalls();
    void DeleteBricks();
    void DeleteBonuses();
    void SetAllNeedRepaint(bool background);
    void RepaintWhatsNeeded();
    void FillWhatsNeed();
    void PaintWhatsNeed();
    static void CorrectOffsetAndAngle(Ball *ball, FloatRECT barrierRect, int numOfIntersection);
    void DeleteWhatsNeeded();
    static void CorrectOffsetAndAngleByPlatform(Ball *ball, FloatRECT platform, int numOfIntersection);
    static BonusType RandomizeBonus();
    void BeginAgainThisLevel();
    void UseBonus(Bonus *bonus);
    void GameProcessing();
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
    void MovePlatformLeft();
    void MovePlatformRight();
};


#endif //ARKANOID_GAMESESSION_H
