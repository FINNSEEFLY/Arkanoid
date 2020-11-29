
#include <iostream>
#include <windows.h>
#include "gdiplus.h"
#include "GameSession.h"
#include "Complementary.h"


GameSession *gameSession;
bool isLeftButtonDown = false;

// Обработка событий главного окна
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR lpCmdLine,
                     int nCmdShow) {
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

    WNDCLASSEX wcex;
    HWND hWnd;
    MSG msg;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = (HICON)LoadImageA(hInstance,"IDI_ICON1",IMAGE_ICON,256,256,0);
    wcex.hIconSm = wcex.hIcon;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "ArkanoidWindowClass";
    wcex.hIconSm = wcex.hIcon;

    RegisterClassEx(&wcex);


    hWnd = CreateWindow("ArkanoidWindowClass",  // Указатель на зарегистрированное имя класса
                        "Arkanoid The Game",    // Указатель на имя окна
                        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,    // Стиль окна
                        CW_USEDEFAULT,          // Горизонтальная позиция окна
                        0,                      // Вертикальная позиция окна
    /*CW_USEDEFAULT*/1440,  // Ширина окна
                        810,                    // Высота окна
                        NULL,                   // Дескриптор родительского или окна владельца
                        NULL,                   // Дескриптор меню или идентификатор дочернего окна
                        hInstance,              // Дескриптор экземпляра приложения
                        NULL);                  // Указатель на данные создания окна

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0)) {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    Gdiplus::GdiplusShutdown(gdiplusToken);
    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
                         WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE:
            gameSession = new GameSession(hWnd);
        case WM_PAINT:
            gameSession->Repaint();
            break;
        case WM_KEYDOWN:
            switch (wParam) {
                case VK_LEFT:
                    if (!gameSession->IsPaused()  && !gameSession->IsShowingLB()) {
                        gameSession->MovePlatformLeft();
                        InvalidateRect(hWnd,NULL,false);
                    }
                    break;
                case VK_RIGHT:
                    if (!gameSession->IsPaused()  && !gameSession->IsShowingLB()) {
                        gameSession->MovePlatformRight();
                        InvalidateRect(hWnd,NULL,false);
                    }
                    break;
                case VK_ESCAPE:
                    if (!gameSession->IsShowingLB()) {
                        gameSession->SwitchPause();
                    }
                    break;
                case VK_SPACE:
                    gameSession->TryToStartGame();
                    break;
                case VK_TAB:
                    if (!gameSession->IsPaused()) {
                        gameSession->SwitchShowingLB();
                    }
            }
            break;
        case WM_LBUTTONDOWN: {
            isLeftButtonDown = true;
            if (!gameSession->IsPaused()  && !gameSession->IsShowingLB()) {
                int offsetX = LOWORD(lParam);
                gameSession->MovePlatform(offsetX);
                InvalidateRect(hWnd, NULL, false);
            }
        }
            break;
        case WM_LBUTTONUP:
            isLeftButtonDown = false;
            break;
        case WM_MOUSEMOVE:
            if (isLeftButtonDown && !gameSession->IsPaused() && !gameSession->IsShowingLB()) {
                int offsetX = LOWORD(lParam);
                gameSession->MovePlatform(offsetX);
                InvalidateRect(hWnd,NULL,false);
            }
            break;
        case WM_SIZE:
            gameSession->ResizeEvent();
            break;
        case WM_GETMINMAXINFO: {
            LPMINMAXINFO lpMMI = (LPMINMAXINFO) lParam;
            gameSession->PreparerResize(lpMMI);
            break;
        }
        case WM_MOVE:
            gameSession->SetAllNeedRepaint(true);
            break;
        case WM_ACTIVATE:
            gameSession->SetAllNeedRepaint(true);
            break;
        case WM_DESTROY:
            delete gameSession;
            PostQuitMessage(0);

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
