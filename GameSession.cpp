//
// Created by FINNSEEFLY on 22.11.2020.
//

#include <fstream>
#include "GameSession.h"
#include "iostream"
#include "Complementary.h"
#include "algorithm"


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

    fireBallPic = new Gdiplus::Image(FIREBALL_PIC_PATH);
    bonusBallPic = new Gdiplus::Image(BONUS_BALL_PATH);
    bonusCutPic = new Gdiplus::Image(BONUS_CUT_PATH);
    bonusExpandPic = new Gdiplus::Image(BONUS_EXPAND_PATH);
    bonusFireBallPic = new Gdiplus::Image(BONUS_FIREBALL_PATH);
    bonusEXP1Pic = new Gdiplus::Image(BONUS_EXP1_PATH);
    bonusEXP2Pic = new Gdiplus::Image(BONUS_EXP2_PATH);
    bonusEXP3Pic = new Gdiplus::Image(BONUS_EXP3_PATH);
    bonusEXP4Pic = new Gdiplus::Image(BONUS_EXP4_PATH);
    bonusEXP5Pic = new Gdiplus::Image(BONUS_EXP5_PATH);

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

    brush = CreateSolidBrush(RGB(0, 0, 0));

    leftSide.left = LEFT_SIDE_LEFT;
    leftSide.right = LEFT_SIDE_RIGHT;
    leftSide.top = LEFT_SIDE_TOP;
    leftSide.bottom = LEFT_SIDE_BOTTOM;

    rightSide.left = RIGHT_SIDE_LEFT;
    rightSide.right = RIGHT_SIDE_RIGHT;
    rightSide.top = RIGHT_SIDE_TOP;
    rightSide.bottom = RIGHT_SIDE_BOTTOM;

    downSide.left = DOWN_SIDE_LEFT;
    downSide.right = DOWN_SIDE_RIGHT;
    downSide.top = DOWN_SIDE_TOP;
    downSide.bottom = DOWN_SIDE_BOTTOM;

    upSide.left = UP_SIDE_LEFT;
    upSide.right = UP_SIDE_RIGHT;
    upSide.top = UP_SIDE_TOP;
    upSide.bottom = UP_SIDE_BOTTOM;

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

    delete fireBallPic;
    delete bonusBallPic;
    delete bonusCutPic;
    delete bonusExpandPic;
    delete bonusFireBallPic;
    delete bonusEXP1Pic;
    delete bonusEXP2Pic;
    delete bonusEXP3Pic;
    delete bonusEXP4Pic;
    delete bonusEXP5Pic;

    DeleteBricks();
    DeleteBalls();
    DeleteBonuses();

    DeleteObject(brush);
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
    GetWindowRect(hWnd, &windowRect);
    if (windowRect.right != prevWindowRect.right ||
        windowRect.left != prevWindowRect.left ||
        windowRect.top != prevWindowRect.top ||
        windowRect.bottom != prevWindowRect.bottom) {
        prevWindowRect.bottom = windowRect.bottom;
        prevWindowRect.left = windowRect.left;
        prevWindowRect.top = windowRect.top;
        prevWindowRect.right = windowRect.right;
        SetAllNeedRepaint(true);
    }
/*    std::cout << "__________________ " << ps.rcPaint.top << " " << ps.rcPaint.bottom << " " << ps.rcPaint.left << " "
              << ps.rcPaint.right << " -------------" << std::endl;*/

    if (ps.rcPaint.bottom - ps.rcPaint.top != clientHeight || ps.rcPaint.right - ps.rcPaint.left != clientWidth) {
        SetAllNeedRepaint(true);
    }
    if (isNeedRepaintBackground) {
        graphics->DrawImage(backgroundPic, backgroundX0, backgroundY0, backgroundWidth, backgroundHeight);
        graphics->DrawImage(gameZonePic, gameBoxX0, gameBoxY0, gameBoxSide, gameBoxSide);
        SetAllNeedRepaint(false);
    }
    RepaintController();

    if (oldLevel != level || isNeedRepaintLevel) {
        FillRect(memDC, &levelTextRect, brush);
        DrawTextA(memDC, ConvertIntToLPWSTR(level), -1, (LPRECT) &levelTextRect,
                  DT_CENTER | DT_SINGLELINE | DT_VCENTER);
        oldLevel = level;
        isNeedRepaintLevel = false;
    }
    if (oldScore != score || isNeedRepaintScore) {
        FillRect(memDC, &scoreTextRect, brush);
        DrawTextA(memDC, ConvertIntToLPWSTR(score), -1, (LPRECT) &scoreTextRect,
                  DT_CENTER | DT_SINGLELINE | DT_VCENTER);
        oldScore = score;
        isNeedRepaintScore = false;
    }
    if (oldLives != lives || isNeedRepaintLives) {
        FillRect(memDC, &livesTextRect, brush);
        DrawTextA(memDC, ConvertIntToLPWSTR(lives), -1, (LPRECT) &livesTextRect,
                  DT_CENTER | DT_SINGLELINE | DT_VCENTER);
        oldLives = lives;
        isNeedRepaintLives = false;
    }
    if (isGamePaused) {
        graphics->DrawImage(pausePic, gameBoxX0, gameBoxY0, gameBoxSide, gameBoxSide);
    }
    CompletionFontDrawing(hFont);
    CompletionPaintingBEP();
    if (!isGamePaused && isGameStarted && !isWaitForStarted) {
        InvalidateRgn(hWnd, NULL, false);
    }
}

void GameSession::RepaintController() {
    if (lives == 0) {
        // проигрыш все дела
        isGameStarted = false;
        isGamePaused = false;
        isNeedGeneration = true;
        isWaitForStarted = false;
        isNeedRepaintBackground = true;
        score = 0;
        lives = 3;
        level = 1;
        isFireBall = false;
        delete platform;
        platform = new Platform(gameZoneX0, gameZoneY0, platformPic, scale, DEFAULT_PLATFORM_OFFSET_X,
                                DEFAULT_PLATFORM_OFFSET_Y);
    }
    if (isNeedGeneration) {
        DeleteBalls();
        DeleteBricks();
        DeleteBonuses();
        numOfBricks = GenerateBricks(level);
        balls.push_back(new Ball(gameZoneX0, gameZoneY0, ballPic, scale,
                                 platform->GetRealWidth() / 2 + platform->GetRealOffsetX() - ballPic->GetWidth() / 2,
                                 platform->GetOffsetY() - 1 - ballPic->GetHeight(), DEFAULT_SPEED, DEFAULT_ANGLE));
        numOfBalls = 1;
        isNeedGeneration = false;
        isWaitForStarted = true;
        SetAllNeedRepaint(true);
    }
    if (isGameStarted && !isGamePaused) {
        GameProcessing();
    }
    RepaintWhatsNeeded();
    DeleteWhatsNeeded();
}

void GameSession::BeginAgainThisLevel() {
    balls.push_back(new Ball(gameZoneX0, gameZoneY0, ballPic, scale,
                             platform->GetRealWidth() / 2 + platform->GetRealOffsetX() -
                             ballPic->GetWidth() / 2,
                             platform->GetOffsetY() - 1 - ballPic->GetHeight(), DEFAULT_SPEED,
                             DEFAULT_ANGLE));
    isGameStarted = false;
    isGamePaused = false;
    isNeedGeneration = false;
    isWaitForStarted = true;
    numOfBalls = 1;
    isFireBall = false;
    RepaintWhatsNeeded();
    DeleteWhatsNeeded();
    return;

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

void GameSession::CalculateGameZone() {
    gameZoneY0 = gameBoxY0 + DEFAULT_GAME_ZONE_TOP * scale;
    gameZoneX0 = gameBoxX0;
}

int GameSession::GenerateBricks(int numOfLevel) {
    int Width;
    int Height;
    int numOfBlocks = 0;
    std::string filename = RESOURCE_ROOT;
    filename += LVL_DIR;
    filename += ConvertIntToString(numOfLevel);
    filename += LVL_EXTENSION;
    std::ifstream reader(filename);
    if (!reader.is_open()) return -1;
    reader >> Width;
    reader >> Height;
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Width; j++) {
            int brickType;
            reader >> brickType;
            Brick *brick;
            brick = BrickFactory(j, i, brickType);
            if (brick == nullptr) continue;
            bricks.push_back(brick);
            numOfBlocks++;
        }
    }
    reader.close();
    return numOfBlocks;
}

Brick *GameSession::BrickFactory(int brickPosX, int brickPosY, int brickType) {
    switch (brickType) {
        case BRICK_NUM_NULL:
            return nullptr;
        case BRICK_NUM_PURPLE:
            return new Brick(gameZoneX0, gameZoneY0, purpleBrickPic, scale, brickPosX * BRICK_WIDTH,
                             brickPosY * BRICK_HEIGHT, BRICK_HITS_PURPLE, BRICK_PRICE_PURPLE, BRICK_TYPE_PURPLE);
        case BRICK_NUM_BLUE:
            return new Brick(gameZoneX0, gameZoneY0, blueBrickPic, scale, brickPosX * BRICK_WIDTH,
                             brickPosY * BRICK_HEIGHT, BRICK_HITS_BLUE, BRICK_PRICE_BLUE, BRICK_TYPE_BLUE);
        case BRICK_NUM_GREEN:
            return new Brick(gameZoneX0, gameZoneY0, greenBrickPic, scale, brickPosX * BRICK_WIDTH,
                             brickPosY * BRICK_HEIGHT, BRICK_HITS_GREEN, BRICK_PRICE_GREEN, BRICK_TYPE_GREEN);
        case BRICK_NUM_YELLOW:
            return new Brick(gameZoneX0, gameZoneY0, yellowBrickPic, scale, brickPosX * BRICK_WIDTH,
                             brickPosY * BRICK_HEIGHT, BRICK_HITS_YELLOW, BRICK_PRICE_YELLOW, BRICK_TYPE_YELLOW);
        case BRICK_NUM_RED:
            return new Brick(gameZoneX0, gameZoneY0, redBrickPic, scale, brickPosX * BRICK_WIDTH,
                             brickPosY * BRICK_HEIGHT, BRICK_HITS_RED, BRICK_PRICE_RED, BRICK_TYPE_RED);
        default:
            return nullptr;
    }
}

void GameSession::MovePlatform(float center) {
    platform->Move(center);
    if (isWaitForStarted) {
        balls[0]->SetOffsetX((platform->GetRealWidth() / 2 + platform->GetRealOffsetX() - ballPic->GetWidth() / 2));
    }
}

void GameSession::MovePlatformLeft() {
    platform->MoveLeft();
    if (isWaitForStarted) {
        balls[0]->SetOffsetX((platform->GetRealWidth() / 2 + platform->GetRealOffsetX() - ballPic->GetWidth() / 2));
    }
}

void GameSession::MovePlatformRight() {
    platform->MoveRight();
    if (isWaitForStarted) {
        balls[0]->SetOffsetX((platform->GetRealWidth() / 2 + platform->GetRealOffsetX() - ballPic->GetWidth() / 2));
    }
}

void GameSession::SetResized() {
    SetAllNeedRepaint(true);
}

void GameSession::SwitchPause() {
    isGamePaused = !isGamePaused;
    if (!isGamePaused) {
        SetAllNeedRepaint(true);
        startTick = GetTickCount();
    }
    InvalidateRect(hWnd, NULL, false);
}

bool GameSession::IsPaused() {
    return isGamePaused;
}

void GameSession::SetAllNeedRepaint(bool background) {
    isNeedRepaintBackground = background;
    isNeedRepaintLevel = true;
    isNeedRepaintScore = true;
    isNeedRepaintLives = true;
    for (auto ball: balls) {
        if (!ball->IsDestroyed()) {
            ball->SetNeedRepaint();
        }
        for (auto brick: bricks) {
            if (!brick->IsDestroyed()) {
                brick->SetNeedRepaint();
            }
        }
        for (auto bonus: bonuses) {
            bonus->SetNeedRepaint();
        }
        platform->SetNeedRepaint();
    }
}

void GameSession::TryToStartGame() {
    if (isWaitForStarted && !isGameStarted && !isGamePaused) {
        isWaitForStarted = false;
        isGameStarted = true;
        InvalidateRect(hWnd, NULL, false);
        startTick = GetTickCount();
    }
}

void GameSession::RepaintWhatsNeeded() {
    FillWhatsNeed();
    PaintWhatsNeed();
}

void GameSession::FillWhatsNeed() {
    for (auto ball: balls) {
        if (ball->IsWasFilled()) {
            FillRect(memDC, &ball->repaintRect, brush);
        }

    }
    for (auto brick: bricks) {
        if (brick->IsWasFilled()) {
            FillRect(memDC, &brick->repaintRect, brush);
        }
    }
    for (auto bonus: bonuses) {
        if (bonus->IsWasFilled()) {
            FillRect(memDC, &bonus->repaintRect, brush);
        }
    }

    if (platform->IsWasFilled()) {
        FillRect(memDC, &platform->repaintRect, brush);
    }
}

void GameSession::PaintWhatsNeed() {
    for (auto ball: balls) {
        if (ball->IsNeedRepaint() && !ball->IsDestroyed()) {
            ball->PaintOnGraphics(*graphics);
        }

    }
    for (auto brick: bricks) {
        if (brick->IsNeedRepaint() && !brick->IsDestroyed()) {
            brick->PaintOnGraphics(*graphics);
        }
    }
    for (auto bonus: bonuses) {
        if (bonus->IsNeedRepaint()) {
            bonus->PaintOnGraphics(*graphics);
        }
    }
    if (platform->IsNeedRepaint()) {
        platform->PaintOnGraphics(*graphics);
    }
}

void GameSession::CorrectOffsetAndAngle(Ball *ball, FloatRECT barrierRect, int numOfIntersection) {
    float angle = ball->GetAngle();
    switch (numOfIntersection) {
        case INTERSECTION_NONE:
            break;
        case INTERSECTION_LEFT: {
            ball->SetOffsetX2(barrierRect.left);
            if (angle == 0) {
                ball->SetAngle(fmod(angle + 180, 360));
            } else if (angle > 0 && angle < 90) {
                ball->SetAngle(180 - angle);
            } else if (angle > 270 && angle < 360) {
                ball->SetAngle(540 - angle);
            }
        }
            break;
        case INTERSECTION_UP: {
            ball->SetOffsetY2(barrierRect.top);
            if (angle == 90) {
                ball->SetAngle(fmod(angle + 180, 360));
            } else if (angle > 0 && angle < 90) {
                ball->SetAngle(360 - angle);
            } else if (angle > 90 && angle < 180) {
                ball->SetAngle(360 - angle);
            }

        }
            break;
        case INTERSECTION_RIGHT: {
            ball->SetOffsetX(barrierRect.right);
            if (angle == 180) {
                ball->SetAngle(fmod(angle + 180, 360));
            } else if (angle > 90 && angle < 180) {
                ball->SetAngle(180 - angle);
            } else if (angle > 180 && angle < 270) {
                ball->SetAngle(540 - angle);
            }
        }
            break;
        case INTERSECTION_DOWN: {
            ball->SetOffsetY(barrierRect.bottom);
            if (angle == 270) {
                ball->SetAngle(fmod(angle + 180, 360));
            } else if (angle > 180 && angle < 270) {
                ball->SetAngle(360 - angle);
            } else if (angle > 270 && angle < 360) {
                ball->SetAngle(360 - angle);
            }
        }
            break;
        case INTERSECTION_LEFT_AND_UP: {
            ball->SetOffsetX2(barrierRect.left);
            ball->SetOffsetY2(barrierRect.top);
            if (angle == 45) {
                ball->SetAngle(fmod(angle + 180, 360));
            }

        }
            break;

        case INTERSECTION_RIGHT_AND_UP: {
            ball->SetOffsetX(barrierRect.right);
            ball->SetOffsetY2(barrierRect.top);
            if (angle == 135) {
                ball->SetAngle(fmod(angle + 180, 360));
            }
        }
            break;
        case INTERSECTION_RIGHT_AND_DOWN: {
            ball->SetOffsetX(barrierRect.right);
            ball->SetOffsetY(barrierRect.bottom);
            if (angle == 225) {
                ball->SetAngle(fmod(angle + 180, 360));
            }
        }
            break;

        case INTERSECTION_LEFT_AND_DOWN: {
            ball->SetOffsetX2(barrierRect.left);
            ball->SetOffsetY(barrierRect.bottom);
            if (angle == 315) {
                ball->SetAngle(fmod(angle + 180, 360));
            }
        }
            break;
        case INTERSECTION_INSIDE: {
            std::cout << "INTERSECTION_INSIDE" << std::endl;
        }
            break;
    }
}

void GameSession::DeleteWhatsNeeded() {
    for (auto ball: balls) {
        if (ball->IsDestroyed()) {
            auto newEnd = std::remove(balls.begin(), balls.end(), ball);
            balls.erase(newEnd, balls.end());
            delete ball;
        }
    }
    for (auto brick: bricks) {
        if (brick->IsDestroyed()) {
            auto newEnd = std::remove(bricks.begin(), bricks.end(), brick);
            bricks.erase(newEnd, bricks.end());
            delete brick;
        }
    }
    for (auto bonus: bonuses) {
        if (bonus->IsDestroyed()) {
            auto newEnd = std::remove(bonuses.begin(), bonuses.end(), bonus);
            bonuses.erase(newEnd, bonuses.end());
            delete bonus;
        }
    }
}

void GameSession::CorrectOffsetAndAngleByPlatform(Ball *ball, FloatRECT platform, int numOfIntersection) {
    float angle = ball->GetAngle();
    switch (numOfIntersection) {
        case INTERSECTION_NONE:
            break;
        case INTERSECTION_UP: {
            srand(GetTickCount());
            ball->SetOffsetY2(platform.top);
            FloatRECT ballRect = ball->GetRECT();
            float ballCenter = (ballRect.right - ballRect.left) / 2;
            float platformCenter = (platform.right - platform.left) / 2;
            float distanceBtwBallAndPlatform = abs(ballCenter - platformCenter);
            float dotCoefficient = distanceBtwBallAndPlatform / platformCenter;
            ball->SetAngle(360 - angle * dotCoefficient * (float) (500 + rand() % 1000) / 1000);
/*            if (angle > 0 && angle < 90) {
                ball->SetAngle(360 - angle);
            } else if (angle > 90 && angle < 180) {
                ball->SetAngle(360 - angle);
            }*/
        }
    }
}

BonusType GameSession::RandomizeBonus() {
    srand(GetTickCount());
    int random = rand() % 3;
    if (random == 0) return BONUS_NONE;
    random = 1 + rand() % 16;
    if (random >= 1 && random <= 4) return BONUS_EXPAND;
    if (random >= 5 && random <= 8) return BONUS_CUT;
    if (random >= 9 && random <= 12) return BONUS_MORE_BALLS;
    if (random >= 13 && random <= 15) return BONUS_EXPERIENCE;
    if (random == 16) return BONUS_MORE_BALLS;
    return BONUS_NONE;
}

Bonus *GameSession::BonusFactory(float offsetX, float offsetY, BonusType bonusType, BrickType brickType) {
    switch (bonusType) {
        case BONUS_NONE:
            return nullptr;
        case BONUS_MORE_BALLS:
            return new Bonus(gameZoneX0, gameZoneY0, bonusBallPic, scale, offsetX, offsetY, BONUS_MORE_BALLS, 0);
        case BONUS_CUT:
            return new Bonus(gameZoneX0, gameZoneY0, bonusCutPic, scale, offsetX, offsetY, BONUS_CUT, 0);
        case BONUS_FIREBALL:
            return new Bonus(gameZoneX0, gameZoneY0, bonusFireBallPic, scale, offsetX, offsetY, BONUS_FIREBALL, 0);
        case BONUS_EXPAND:
            return new Bonus(gameZoneX0, gameZoneY0, bonusExpandPic, scale, offsetX, offsetY, BONUS_EXPAND, 0);
        case BONUS_EXPERIENCE: {
            switch (brickType) {
                case BRICK_TYPE_PURPLE:
                    return new Bonus(gameZoneX0, gameZoneY0, bonusEXP1Pic, scale, offsetX, offsetY, BONUS_EXPERIENCE,
                                     BRICK_PRICE_PURPLE * 5 * 5);
                case BRICK_TYPE_GREEN:
                    return new Bonus(gameZoneX0, gameZoneY0, bonusEXP3Pic, scale, offsetX, offsetY, BONUS_EXPERIENCE,
                                     BRICK_PRICE_GREEN * 5 * 5);
                case BRICK_TYPE_BLUE:
                    return new Bonus(gameZoneX0, gameZoneY0, bonusEXP2Pic, scale, offsetX, offsetY, BONUS_EXPERIENCE,
                                     BRICK_PRICE_BLUE * 5 * 5);
                case BRICK_TYPE_RED:
                    return new Bonus(gameZoneX0, gameZoneY0, bonusEXP5Pic, scale, offsetX, offsetY, BONUS_EXPERIENCE,
                                     BRICK_PRICE_RED * 5 * 5);
                case BRICK_TYPE_YELLOW:
                    return new Bonus(gameZoneX0, gameZoneY0, bonusEXP4Pic, scale, offsetX, offsetY, BONUS_EXPERIENCE,
                                     BRICK_PRICE_YELLOW * 5 * 5);
                default:
                    return nullptr;
            }
        }
        default:
            return nullptr;
    }


}

void GameSession::UseBonus(Bonus *bonus) {
    switch (bonus->GetBonusType()) {
        case BONUS_EXPERIENCE: {
            score += bonus->GetPrice();
        }
            break;
        case BONUS_EXPAND: {
            platform->IncSizeCoefficient();
        }
            break;
        case BONUS_FIREBALL: {
            isFireBall = true;
        }
            break;
        case BONUS_CUT: {
            platform->DecSizeCoefficient();
        }
        case BONUS_MORE_BALLS: {
            std::vector<Ball *> tmpBalls;
            for (auto ball:balls) {
                FloatRECT ballRect = ball->GetRECT();
                Ball *newBall = new Ball(gameZoneX0, gameZoneY0, ballPic, scale, ballRect.left, ballRect.top,
                                         ball->GetSpeed(), fmod(ball->GetAngle() + 90, 360));
                tmpBalls.push_back(newBall);
            }
            tmpBalls.clear();
        }
        bonus->SetDestroyed();
        bonus->SetRepaintRECT();
    }
}

void GameSession::GameProcessing() {
    endTick = GetTickCount();
    if (startTick == endTick) return;
    for (; startTick <= endTick; startTick++) {
        for (auto ball: balls) {
            ball->CalculateNextPoint(DEFAULT_TIME);
            CorrectOffsetAndAngleByPlatform(ball, platform->GetRECT(),
                                            ball->GetNumOfIntersection(platform->GetRECT()));
            CorrectOffsetAndAngle(ball, leftSide, ball->GetNumOfIntersection(leftSide));
            CorrectOffsetAndAngle(ball, rightSide, ball->GetNumOfIntersection(rightSide));
            CorrectOffsetAndAngle(ball, upSide, ball->GetNumOfIntersection(upSide));
            if (ball->GetNumOfIntersection(downSide) != 0) {
                numOfBalls--;
                ball->SetDestroyed();
                if (numOfBalls == 0) {
                    lives--;
                    if (lives == 0) break;
                    else {
                        BeginAgainThisLevel();
                    }
                }
            }
            for (auto brick: bricks) {
                if (brick->IsDestroyed()) continue;
                int numOfIntersection = ball->GetNumOfIntersection(brick->GetRECT());
                if (numOfIntersection == 0) continue;
                numOfBricks -= brick->HitTheBrick(isFireBall);
                FloatRECT brickRect = brick->GetRECT();
                if (brick->IsDestroyed()) {
                    score += brick->GetPrice();

                    Bonus *bonus = BonusFactory((brickRect.right - brickRect.left) / 2 + brickRect.left,
                                                (brickRect.bottom - brickRect.top) / 2 + brickRect.top,
                                                RandomizeBonus(), brick->GetBrickType());
                    if (bonus) {
                        bonuses.push_back(bonus);
                    }
                }
                if (!isFireBall) {
                    CorrectOffsetAndAngle(ball, brickRect, numOfIntersection);
                    if (numOfBricks == 0) {
                        isGameStarted = false;
                        isGamePaused = false;
                        isNeedGeneration = true;
                        isWaitForStarted = false;
                        numOfBalls = 1;
                        level += 1;
                        RepaintWhatsNeeded();
                        DeleteWhatsNeeded();
                    }
                }
            }
        }
        for (auto bonus:bonuses) {
            bonus->CalculateNextPoint(DEFAULT_TIME);
            if (bonus->GetNumOfIntersection(platform->GetRECT())) {
                UseBonus(bonus); continue;
            }
            if (bonus->GetNumOfIntersection(downSide) == INTERSECTION_DOWN) {
                bonus->SetDestroyed();
            }
            for(auto brick:bricks) {
                int numOfIntersection = bonus->GetNumOfIntersection(brick->GetRECT());
                if (numOfIntersection==0) continue;
                brick->PrepareToRelocate();
            }
        }
    }

}






