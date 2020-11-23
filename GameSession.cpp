//
// Created by FINNSEEFLY on 22.11.2020.
//

#include <sstream>
#include "GameSession.h"
#include "iostream"
#include "Resources.h"


GameSession::GameSession(const HWND hwnd) : hWnd(hwnd) {
    backgroundPic = new Gdiplus::Image(L"res\\interface\\SpaceBlurred1080p.jpg");
    PausePic = new Gdiplus::Image(L"res\\interface\\Pause.png");
    gameZonePic = new Gdiplus::Image(L"res\\interface\\GamingZone.png");
    platformPic = new Gdiplus::Image(L"res\\platform\\platform.png");
    ballPic = new Gdiplus::Image(L"res\\ball\\Ball32x32.png");
    blueBrickPic = new Gdiplus::Image(L"res\\bricks\\BlueBrick.png");
    GrinBrickPic = new Gdiplus::Image(L"res\\bricks\\GrinBrick.png");
    PurpleBrickPic = new Gdiplus::Image(L"res\\bricks\\PurpleBrick.png");
    RedBrickPic = new Gdiplus::Image(L"res\\bricks\\RedBrick.png");
    YellowBrickPic = new Gdiplus::Image(L"res\\bricks\\YellowBrick.png");

    level = 1;
    lives = 3;
    score = 0;

    lf.lfCharSet = DEFAULT_CHARSET;
    lf.lfPitchAndFamily = DEFAULT_PITCH;
    strcpy(lf.lfFaceName, "Open Sans");
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
/*    zeroRect.left = 0;
    zeroRect.top = 0;
    zeroRect.right = 0;
    zeroRect.bottom = 0;*/

    platform = new Platform(gameZoneX0, gameZoneY0, platformPic, scale, DEFAULT_PLATFORM_OFFSET_X,
                            DEFAULT_PLATFORM_OFFSET_Y);
}

GameSession::~GameSession() {
    delete backgroundPic;
    delete PausePic;
    delete gameZonePic;
    delete platformPic;
    delete ballPic;
    delete blueBrickPic;
    delete GrinBrickPic;
    delete PurpleBrickPic;
    delete RedBrickPic;
    delete YellowBrickPic;
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
}

void GameSession::Repaint() {
    InitPaintBEP();
    PrepareFontDrawing(hFont);
/*    std::cout << "__________________ " << ps.rcPaint.top << " " << ps.rcPaint.bottom << " " << ps.rcPaint.left << " "
              << ps.rcPaint.right << " -------------" << std::endl;*/
    graphics->DrawImage(backgroundPic, backgroundX0, backgroundY0, backgroundWidth, backgroundHeight);
    graphics->DrawImage(gameZonePic, gameBoxX0, gameBoxY0, gameBoxSide, gameBoxSide);
    platform->PaintOnGraphics(*graphics);
    DrawTextA(memDC, ConvertIntToStr(level), -1, (LPRECT) &levelTextRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
    DrawTextA(memDC, ConvertIntToStr(score), -1, (LPRECT) &scoreTextRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
    DrawTextA(memDC, ConvertIntToStr(lives), -1, (LPRECT) &livesTextRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
    CompletionFontDrawing(hFont);
    CompletionPaintingBEP();

/*    std::cout << "$$$$$$$$$$$$$$$$ " << zeroRect.top << " " << zeroRect.bottom << " " << zeroRect.left << " "
              << zeroRect.right << " $$$$$$$$$$$$$$$$" << std::endl;
    InvalidateRect(hWnd, &zeroRect, false);*/
}

void GameSession::PreparerResize(LPMINMAXINFO &lpminmaxinfo) {
    lpminmaxinfo->ptMinTrackSize.x = 540 + 20;
    lpminmaxinfo->ptMinTrackSize.y = 540 + 40;
}

void GameSession::InitPaintBEP() {
    hdc = BeginPaint(hWnd, &ps);
    memDC = CreateCompatibleDC(hdc);
    hBM = CreateCompatibleBitmap(hdc, clientWidth, clientHeight);
    oldbmp = (HBITMAP) SelectObject(memDC, hBM);
    graphics = new Gdiplus::Graphics(memDC);
}

void GameSession::CompletionPaintingBEP() {
    BitBlt(hdc, 0, 0, clientWidth, clientHeight, memDC, 0, 0, SRCCOPY);
    SelectObject(memDC, oldbmp);
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
        scale = gameBoxSide / (float)gameZonePic->GetWidth();
    } else {
        gameBoxSide = clientHeight;
        gameBoxX0 = (clientWidth - gameBoxSide) / 2;
        gameBoxY0 = 0;
        scale = gameBoxSide / (float)gameZonePic->GetHeight();
    }
}

LPCSTR GameSession::ConvertIntToStr(int value) {
    std::stringstream s;
    s << std::scientific << value;
    return s.str().c_str();
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
    SelectObject(memDC, hfont);
    SetTextColor(memDC, RGB(255, 255, 255));
    SetBkColor(memDC, RGB(0, 0, 0));
}

void GameSession::CompletionFontDrawing(HFONT &hfont) {
    DeleteObject(hfont);
}

void GameSession::CompletionPaintingGRP() {
    BitBlt(hdc, 0, 0, clientWidth, clientHeight, memDC, 0, 0, SRCCOPY);
    SelectObject(memDC, oldbmp);
    DeleteObject(hBM);
    DeleteDC(memDC);
    ReleaseDC(hWnd, hdc);
    delete graphics;
}

void GameSession::InitPaintGRP() {
    hdc = GetDC(hWnd);
    memDC = CreateCompatibleDC(hdc);
    hBM = CreateCompatibleBitmap(hdc, clientWidth, clientHeight);
    oldbmp = (HBITMAP) SelectObject(memDC, hBM);
    graphics = new Gdiplus::Graphics(memDC);
}

void GameSession::CalculateGameZone() {
    gameZoneY0 = gameBoxY0 + DEFAULT_GAME_ZONE_TOP * scale;
    gameZoneX0 = gameBoxX0;
}
