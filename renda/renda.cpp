#ifndef UNICODE
#define UNICODE
#endif 

#include <no_sal2.h>
#include <windows.h>
#include <wchar.h>

#include "GlobalVariants.h"
#include "WindowManager.h"
#include "Execution.h"
#include "Input.h"


// 関数宣言-------------------------
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void SendRightClick();
void StopRenda();
void StartRenda();
void StartKeyHook();
void StopKeyHook();


int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow) // ウィンドウが立ち上がるときの処理
{
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

	g_hInstance = hInstance;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"連打ソフト by Ryoncy",              // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        // W_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        100 , 100 ,300 ,500, 

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // 自分のやりたことを書く
    CreateMainWindow(hwnd, hInstance);
    RefreshMainWindow();
    StartKeyHook();

    // loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    StopKeyHook();


    return 0;
}

void StartKeyHook()
{
	g_hKeyHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
}

void StopKeyHook()
{
    if (g_hKeyHook)
    {
        UnhookWindowsHookEx(g_hKeyHook);
        g_hKeyHook = NULL;
    }
}