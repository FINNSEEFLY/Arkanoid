#include <iostream>
#include <windows.h>
#include "gdiplus.h"
#include "GameSession.h"


HINSTANCE mainInstance;
GameSession *gameSession;
bool isLeftButtonDown = false;
WNDCLASSEX mainWindowClass;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

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
    mainInstance = hInstance;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = (HICON) LoadImageA(hInstance, "IDI_ICON1", IMAGE_ICON, 256, 256, 0);
    wcex.hIconSm = wcex.hIcon;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "ArkanoidWindowClass";
    wcex.hIconSm = wcex.hIcon;
    mainWindowClass = wcex;

    RegisterClassEx(&wcex);


    hWnd = CreateWindow("ArkanoidWindowClass",  // Указатель на зарегистрированное имя класса
                        "Arkanoid The Game",    // Указатель на имя окна
                        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX |
                        WS_MAXIMIZEBOX,         // Стиль окна
                        CW_USEDEFAULT,          // Горизонтальная позиция окна
                        0,                      // Вертикальная позиция окна
                        1440,                   // Ширина окна
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
        case WM_PAINT:
            gameSession->Repaint();
            break;
        case WM_LBUTTONDOWN: {
            isLeftButtonDown = true;
            if (!gameSession->IsPaused() && !gameSession->IsShowingLB()) {
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
                InvalidateRect(hWnd, NULL, false);
            }
            break;
        case WM_KEYDOWN:
            switch (wParam) {
                case VK_LEFT:
                    if (!gameSession->IsPaused() && !gameSession->IsShowingLB()) {
                        gameSession->MovePlatformLeft();
                        InvalidateRect(hWnd, NULL, false);
                    }
                    break;
                case VK_RIGHT:
                    if (!gameSession->IsPaused() && !gameSession->IsShowingLB()) {
                        gameSession->MovePlatformRight();
                        InvalidateRect(hWnd, NULL, false);
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
        case WM_SIZE:
            gameSession->ResizeEvent();
            break;
        case WM_GETMINMAXINFO: {
            auto lpMMI = (LPMINMAXINFO) lParam;
            gameSession->PreparerResize(lpMMI);
        }
            break;
        case WM_MOVE:
            gameSession->SetAllNeedRepaint(true);
            break;
        case WM_ACTIVATE:
            gameSession->SetAllNeedRepaint(true);
            break;
        case WM_NEED_A_DIALOG_BOX: {
            INT_PTR result = DialogBoxA(mainInstance, MAKEINTRESOURCE(129), hWnd, DialogProc);
            if (result != 0) {
                auto *str = (std::string *) result;
                if (!str->empty())
                    gameSession->AddToScoreBoard(str);
            }
        }
            break;
        case WM_CREATE:
            gameSession = new GameSession(hWnd);
            break;
        case WM_DESTROY:
            delete gameSession;
            PostQuitMessage(0);
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_INITDIALOG:
            HICON hIcon;
            hIcon = mainWindowClass.hIcon;
            if (hIcon) {
                SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM) hIcon);
            }
            return (INT_PTR) TRUE;
        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK) {
                TCHAR *buf;
                int len;
                HWND MainInputEdit = GetDlgItem(hDlg, 1000);
                buf = (TCHAR *) malloc(len = ((GetWindowTextLength(MainInputEdit) + 1) * sizeof(TCHAR)));
                if (buf != NULL) {
                    GetWindowText(MainInputEdit, buf, len);
                }
                std::string editStr = std::string(buf);
                free(buf);
                std::string *tmpStr = new std::string(editStr);
                EndDialog(hDlg, (INT_PTR) tmpStr);
                return (INT_PTR) TRUE;
            } else if (LOWORD(wParam) == IDCANCEL) {
                EndDialog(hDlg, 0);
                return (INT_PTR) TRUE;
            }
            break;
    }
    return (INT_PTR) FALSE;
};
