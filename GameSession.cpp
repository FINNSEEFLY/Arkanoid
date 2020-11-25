//
// Created by FINNSEEFLY on 22.11.2020.
//

#include <sstream>
#include <fstream>
#include "GameSession.h"
#include "iostream"
#include "Complementary.h"


GameSession::GameSession(const HWND hwnd) : hWnd(hwnd) {
    backgroundPic = new Gdiplus::Image(BACKGROUND_PIC_PATH);
    pausePic = new Gdiplus::Image(PAUSE_PIC_PATH);
    gameZonePic = new Gdiplus::Image(GAME_BOX_PIC_PATH);
    platformPic = new Gdiplus::Image(PLATFORM_PIC_PATH);
    ballPic = new Gdiplus::Image(BALL_PIC_PATH);
    blueBrickPic = new Gdiplus::Image(BLUE_BRICK_PIC_PATH);
    greenBrickPic = new Gdiplus::Image(GREEN_BRICK_PIC_PATH);
    purpleBrickPic = new Gdiplus::Image(PURPLE_BRICK_PIC_PATH);
    redBrickPic = new Gdiplus::Image(RED_BRICK_PIC_PATH);
    yellowBrickPic = new Gdiplus::Image(YELLOW_BRICK_PIC_PATH);

    level = 1;
    lives = 3;
    score = 0;

    lf.lfCharSet = DEFAULT_CHARSET;
    lf.lfPitchAndFamily = DEFAULT_PITCH;
    strcpy(lf.lfFaceName, "Arial");
    lf.lfHeight = DEFAULT_FONT_HEIGHT;
    lf.lfWidth = DEFAULT_FONT_WIDTH;
    lf.lfWeight = DEFAULT_FONT_WEIGHT;
    lf.lfEscapement = DEFAULT_FONT_ESCAPEMENT;
    lf.lfUnderline = DEFAULT_FONT_UNDERLINE;
    lf.lfStrikeOut = DEFAULT_FONT_STRIKE_OUT;
    lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    lf.lfItalic = DEFAULT_FONT_ITALIC;
    lf.lfQuality = ANTIALIASED_QUALITY;

    levelTextRect.bottom = TEXT_BOTTOM;
    levelTextRect.left = LEVEL_LEFT;
    levelTextRect.right = LEVEL_RIGHT;
    levelTextRect.top = TEXT_TOP;

    scoreTextRect.bottom = TEXT_BOTTOM;
    scoreTextRect.left = SCORE_LEFT;
    scoreTextRect.right = SCORE_RIGHT;
    scoreTextRect.top = TEXT_TOP;

    livesTextRect.bottom = TEXT_BOTTOM;
    livesTextRect.left = LIVES_LEFT;
    livesTextRect.right = LIVES_RIGHT;
    livesTextRect.top = TEXT_TOP;

    platform = new Platform(gameZoneX0, gameZoneY0, platformPic, scale, DEFAULT_PLATFORM_OFFSET_X,
                            DEFAULT_PLATFORM_OFFSET_Y);
}

GameSession::~GameSession() {
    delete backgroundPic;
    delete pausePic;
    delete gameZonePic;
    delete platformPic;
    delete ballPic;
    delete blueBrickPic;
    delete greenBrickPic;
    delete purpleBrickPic;
    delete redBrickPic;
    delete yellowBrickPic;
    delete platform;
}

void GameSession::ResizeEvent() {
    GetClientRect(hWnd, &clientRect);
    clientWidth = clientRect.right - clientRect.left;
    clientHeight = clientRect.bottom - clientRect.top;

    CalculateBackground(backgroundX0, backgroundY0, backgroundWidth, backgroundHeight);
    CalculateGameBox(gameBoxX0, gameBoxY0, gameBoxSide, scale);
    CalculateGameZone();

    CalculateFontProperties();
    SetResized();
}

void GameSession::Repaint() {
    InitPaintBEP();
    PrepareFontDrawing(hFont);
/*    std::cout << "__________________ " << ps.rcPaint.top << " " << ps.rcPaint.bottom << " " << ps.rcPaint.left << " "
              << ps.rcPaint.right << " -------------" << std::endl;*/

    RepaintController();
    if (resized) {
        graphics->DrawImage(backgroundPic, backgroundX0, backgroundY0, backgroundWidth, backgroundHeight);
        graphics->DrawImage(gameZonePic, gameBoxX0, gameBoxY0, gameBoxSide, gameBoxSide);
    }
    platform->PaintOnGraphics(*graphics);
    DrawTextA(memDC, ConvertIntToLPWSTR(level), -1, (LPRECT) &levelTextRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
    DrawTextA(memDC, ConvertIntToLPWSTR(score), -1, (LPRECT) &scoreTextRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
    DrawTextA(memDC, ConvertIntToLPWSTR(lives), -1, (LPRECT) &livesTextRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
    if (isGamePaused) {
        graphics->DrawImage(pausePic, gameBoxX0, gameBoxY0, gameBoxSide, gameBoxSide);
    }
    CompletionFontDrawing(hFont);
    CompletionPaintingBEP();
    //InvalidateRgn(hWnd, CreateRectRgn(0,0,0,0), false);
}

void GameSession::RepaintController() {
    if (resized) {
        for(auto ball: balls) {
            ball->SetNeedRepaint();
        }
        for(auto brick: bricks) {
            brick->SetNeedRepaint();
        }
        for(auto bonus: bonuses) {
            bonus->SetNeedRepaint();
        }
        platform->SetNeedRepaint();
    }
    if (isNeedGeneration) {
        DeleteBalls();
        DeleteBricks();
        DeleteBonuses();
        GenerateBricks(level);
        balls.push_back(new Ball(gameZoneX0, gameZoneY0, ballPic, scale,
                                 (platform->GetRealWidth() - platform->GetRealOffsetX()) / 2,
                                 platform->GetOffsetY() - 1, DEFAULT_SPEED, DEFAULT_ANGLE));
        isNeedGeneration=false;
        isWaitForStarted=true;
    }
}

void GameSession::DeleteBalls() {
    for (Ball *ball: balls) {
        delete ball;
    }
    balls.clear();
}

void GameSession::DeleteBricks() {
    for (Brick *brick: bricks) {
        delete brick;
    }
    bricks.clear();
}

void GameSession::DeleteBonuses() {
    for (Bonus *bonus: bonuses) {
        delete bonus;
    }
    bonuses.clear();
}

void GameSession::PreparerResize(LPMINMAXINFO &lpminmaxinfo) {
    lpminmaxinfo->ptMinTrackSize.x = MIN_GAME_ZONE_SIDE + 20;
    lpminmaxinfo->ptMinTrackSize.y = MIN_GAME_ZONE_SIDE + 40;
}

void GameSession::InitPaintBEP() {
    hdc = BeginPaint(hWnd, &ps);
    memDC = CreateCompatibleDC(hdc);
    hBM = CreateCompatibleBitmap(hdc, clientWidth, clientHeight);
    oldBmp = (HBITMAP) SelectObject(memDC, hBM);
    graphics = new Gdiplus::Graphics(memDC);
    // Добавлено как костыль, если будет влиять на производительность - удалить
    BitBlt(memDC, 0, 0, clientWidth, clientHeight, hdc, 0, 0, SRCCOPY);
}

void GameSession::CompletionPaintingBEP() {
    BitBlt(hdc, 0, 0, clientWidth, clientHeight, memDC, 0, 0, SRCCOPY);
    DeleteObject(SelectObject(memDC, oldBmp));
    DeleteObject(hBM);
    DeleteDC(memDC);
    EndPaint(hWnd, &ps);
    delete graphics;
}

void GameSession::CalculateBackground(float &backgroundX0, float &backgroundY0, float &backgroundWidth,
                                      float &backgroundHeight) {
    float horizontalCoeff = backgroundPic->GetWidth() / clientWidth;
    float verticalCoeff = backgroundPic->GetHeight() / clientHeight;
    if (horizontalCoeff < verticalCoeff) {
        backgroundWidth = backgroundPic->GetWidth() / horizontalCoeff;
        backgroundHeight = backgroundPic->GetHeight() / horizontalCoeff;
        backgroundY0 = 0 - (backgroundHeight - clientHeight) / 2;
        backgroundX0 = 0;
    } else {
        backgroundWidth = backgroundPic->GetWidth() / verticalCoeff;
        backgroundHeight = backgroundPic->GetHeight() / verticalCoeff;
        backgroundX0 = 0 - (backgroundWidth - clientWidth) / 2;
        backgroundY0 = 0;
    }
}

void GameSession::CalculateGameBox(float &gameBoxX0, float &gameBoxY0, float &gameBoxSide, float &scale) {
    if (clientWidth < clientHeight) {
        gameBoxSide = clientWidth;
        gameBoxY0 = (clientHeight - gameBoxSide) / 2;
        gameBoxX0 = 0;
        scale = gameBoxSide / (float) gameZonePic->GetWidth();
    } else {
        gameBoxSide = clientHeight;
        gameBoxX0 = (clientWidth - gameBoxSide) / 2;
        gameBoxY0 = 0;
        scale = gameBoxSide / (float) gameZonePic->GetHeight();
    }
}

LPCSTR GameSession::ConvertIntToLPWSTR(int value) {
    std::stringstream s;
    s << std::scientific << value;
    return s.str().c_str();
}

std::string GameSession::ConvertIntToString(int value) {
    std::stringstream s;
    s << std::scientific << value;
    return s.str();
}

void GameSession::CalculateFontProperties() {
    lf.lfHeight = DEFAULT_FONT_HEIGHT * scale;
    lf.lfWidth = DEFAULT_FONT_WIDTH * scale;
    lf.lfWeight = DEFAULT_FONT_WEIGHT * scale;

    levelTextRect.bottom = TEXT_BOTTOM * scale + gameBoxY0;
    levelTextRect.left = LEVEL_LEFT * scale + gameBoxX0;
    levelTextRect.right = LEVEL_RIGHT * scale + gameBoxX0;
    levelTextRect.top = TEXT_TOP * scale + gameBoxY0;

    scoreTextRect.bottom = TEXT_BOTTOM * scale + gameBoxY0;
    scoreTextRect.left = SCORE_LEFT * scale + gameBoxX0;
    scoreTextRect.right = SCORE_RIGHT * scale + gameBoxX0;
    scoreTextRect.top = TEXT_TOP * scale + gameBoxY0;

    livesTextRect.bottom = TEXT_BOTTOM * scale + gameBoxY0;
    livesTextRect.left = LIVES_LEFT * scale + gameBoxX0;
    livesTextRect.right = LIVES_RIGHT * scale + gameBoxX0;
    livesTextRect.top = TEXT_TOP * scale + gameBoxY0;
}

void GameSession::PrepareFontDrawing(HFONT &hfont) {
    hfont = CreateFontIndirect(&lf);
    DeleteObject(SelectObject(memDC, hfont));
    SetTextColor(memDC, RGB(255, 255, 255));
    SetBkColor(memDC, RGB(0, 0, 0));
}

void GameSession::CompletionFontDrawing(HFONT &hfont) {
    DeleteObject(hfont);
}

void GameSession::CompletionPaintingGRP() {
    BitBlt(hdc, 0, 0, clientWidth, clientHeight, memDC, 0, 0, SRCCOPY);
    SelectObject(memDC, oldBmp);
    DeleteObject(hBM);
    DeleteDC(memDC);
    ReleaseDC(hWnd, hdc);
    delete graphics;
}

void GameSession::InitPaintGRP() {
    hdc = GetDC(hWnd);
    memDC = CreateCompatibleDC(hdc);
    hBM = CreateCompatibleBitmap(hdc, clientWidth, clientHeight);
    oldBmp = (HBITMAP) SelectObject(memDC, hBM);
    graphics = new Gdiplus::Graphics(memDC);
}

void GameSession::CalculateGameZone() {
    gameZoneY0 = gameBoxY0 + DEFAULT_GAME_ZONE_TOP * scale;
    gameZoneX0 = gameBoxX0;
}

bool GameSession::GenerateBricks(int numOfLevel) {
    int Width;
    int Height;
    std::string filename = RESOURCE_ROOT;
    filename += LVL_DIR;
    filename += ConvertIntToString(numOfLevel);
    filename += LVL_EXTENSION;
    std::ifstream reader(filename);
    if (!reader.is_open()) return false;
    reader >> Width;
    reader >> Height;
    for (int i = 0; i < Width; i++) {
        for (int j = 0; j < Height; j++) {
            int brickType;
            reader >> brickType;
            Brick *brick;
            brick = BrickFactory(i, j, brickType);
            if (brick == nullptr) continue;
            bricks.push_back(brick);
        }
    }
    reader.close();
    return true;
}

Brick *GameSession::BrickFactory(int brickPosX, int brickPosY, int brickType) {
    switch (brickType) {
        case BRICK_NUM_NULL:
            return nullptr;
        case BRICK_NUM_PURPLE:
            return new Brick(gameZoneX0, gameZoneY0, purpleBrickPic, scale, brickPosX * BRICK_WIDTH,
                             brickPosY * BRICK_HEIGHT, BRICK_HITS_PURPLE, BRICK_PRICE_PURPLE);
        case BRICK_NUM_BLUE:
            return new Brick(gameZoneX0, gameZoneY0, blueBrickPic, scale, brickPosX * BRICK_WIDTH,
                             brickPosY * BRICK_HEIGHT, BRICK_HITS_BLUE, BRICK_PRICE_BLUE);
        case BRICK_NUM_GREEN:
            return new Brick(gameZoneX0, gameZoneY0, greenBrickPic, scale, brickPosX * BRICK_WIDTH,
                             brickPosY * BRICK_HEIGHT, BRICK_HITS_GREEN, BRICK_PRICE_GREEN);
        case BRICK_NUM_YELLOW:
            return new Brick(gameZoneX0, gameZoneY0, yellowBrickPic, scale, brickPosX * BRICK_WIDTH,
                             brickPosY * BRICK_HEIGHT, BRICK_HITS_YELLOW, BRICK_PRICE_YELLOW);
        case BRICK_NUM_RED:
            return new Brick(gameZoneX0, gameZoneY0, redBrickPic, scale, brickPosX * BRICK_WIDTH,
                             brickPosY * BRICK_HEIGHT, BRICK_HITS_RED, BRICK_PRICE_RED);
        default:
            return nullptr;
    }
}

void GameSession::MovePlatform(float center) {
    platform->Move(center);
}

void GameSession::SetResized() {
    resized = true;
}



