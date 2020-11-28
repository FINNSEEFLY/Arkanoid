
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
    wcex.hIcon = (HICON) LoadImage(hInstance, "res\\ico\\icon.ico", IMAGE_ICON, 256, 256, LR_LOADFROMFILE);
    wcex.hIconSm = (HICON) LoadImage(hInstance, "res\\ico\\icon.ico", IMAGE_ICON, 256, 256, LR_LOADFROMFILE);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "ArkanoidWindowClass";
    wcex.hIconSm = wcex.hIcon;

    RegisterClassEx(&wcex);


    hWnd = CreateWindow("ArkanoidWindowClass",  // Указатель на зарегистрированное имя класса
                        "Arkanoid The Game",    // Указатель на имя окна
                        WS_OVERLAPPEDWINDOW,    // Стиль окна
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
                    if (!gameSession->IsPaused()) {
                        gameSession->MovePlatformLeft();
                        InvalidateRect(hWnd,NULL,false);
                    }
                    break;
                case VK_RIGHT:
                    if (!gameSession->IsPaused()) {
                        gameSession->MovePlatformRight();
                        InvalidateRect(hWnd,NULL,false);
                    }
                    break;
                case VK_ESCAPE:
                    gameSession->SwitchPause();
                    break;
                case VK_SPACE:
                    gameSession->TryToStartGame();
                    break;
            }
            break;
        case WM_LBUTTONDOWN: {
            isLeftButtonDown = true;
            if (!gameSession->IsPaused()) {
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
            if (isLeftButtonDown && !gameSession->IsPaused()) {
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
        case WM_DESTROY:
            delete gameSession;
            PostQuitMessage(0);
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
