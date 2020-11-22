//
// Created by FINNSEEFLY on 22.11.2020.
//

#include "GameSession.h"
#include "iostream"

GameSession::GameSession(const HWND hwnd) : hWnd(hwnd) {
    backgroundPic = new Gdiplus::Image(L"res\\interface\\SpaceBlurred.jpg");
    PausePic = new Gdiplus::Image(L"res\\interface\\Pause.png");
    gameZonePic = new Gdiplus::Image(L"res\\interface\\GamingZone.png");
    platformPic = new Gdiplus::Image(L"res\\platform\\platform.png");
    ballPic = new Gdiplus::Image(L"res\\ball\\Ball32x32.png");
    blueBrickPic = new Gdiplus::Image(L"res\\bricks\\BlueBrick.png");
    GrinBrickPic = new Gdiplus::Image(L"res\\bricks\\GrinBrick.png");
    PurpleBrickPic = new Gdiplus::Image(L"res\\bricks\\PurpleBrick.png");
    RedBrickPic = new Gdiplus::Image(L"res\\bricks\\RedBrick.png");
    YellowBrickPic = new Gdiplus::Image(L"res\\bricks\\YellowBrick.png");
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
}

void GameSession::ResizeEvent() {
//  Подготовка фона
/*
    Делим src ширину на dst ширину
    Делим src высоту на dst высоту
    Выбираем наименьший коэффициент
    Делим src ширину и src высоту на наименьший коэффициент
    Если был выбран коэфициент от ширины - нужно будет корректировать смещение по высоте
    Если был выбран коэфициент от высоты - нужно будет корректировать смещение по горизонтали
*/
    float backgroundX0 = 0;
    float backgroundY0 = 0;
    GetClientRect(hWnd, &clientRect);
    float clientWidth = clientRect.right - clientRect.left;
    float clientHeight = clientRect.bottom - clientRect.top;
    float backgroundWidth;
    float backgroundHeight;
    float horizontalCoeff = backgroundPic->GetWidth() / clientWidth;
    float verticalCoeff = backgroundPic->GetHeight() / clientHeight;
    if (horizontalCoeff < verticalCoeff) {
        backgroundWidth = backgroundPic->GetWidth() / horizontalCoeff;
        backgroundHeight = backgroundPic->GetHeight() / horizontalCoeff;
        backgroundY0-=(backgroundHeight-clientHeight)/2;
    } else {
        backgroundWidth = backgroundPic->GetWidth() / verticalCoeff;
        backgroundHeight = backgroundPic->GetHeight() / verticalCoeff;
        backgroundX0-=(backgroundWidth-clientWidth)/2;
    }
//  Подготовка игровой зоны


    InitPaint();
    graphics->DrawImage(backgroundPic,backgroundX0,backgroundY0,backgroundWidth,backgroundHeight);
    CompletionPainting();


}

void GameSession::PreparerResize(LPMINMAXINFO &lpminmaxinfo) {
    lpminmaxinfo->ptMinTrackSize.x = 540 + 20;
    lpminmaxinfo->ptMinTrackSize.y = 540 + 40;
}

void GameSession::InitPaint() {
    int clientWidth = clientRect.right - clientRect.left;
    int clientHeight = clientRect.bottom - clientRect.top;
    hdc = BeginPaint(hWnd, &ps);
    memDC = CreateCompatibleDC(hdc);
    hBM = CreateCompatibleBitmap(hdc, clientWidth, clientHeight);
    oldbmp = (HBITMAP)SelectObject(memDC, hBM);
    graphics = new Gdiplus::Graphics(memDC);
}

void GameSession::CompletionPainting() {
    int clientWidth = clientRect.right - clientRect.left;
    int clientHeight = clientRect.bottom - clientRect.top;
    BitBlt(hdc, 0, 0, clientWidth, clientHeight, memDC, 0, 0, SRCCOPY);
    SelectObject(memDC, oldbmp);
    DeleteObject(hBM);
    DeleteDC(memDC);
    delete graphics;
}
