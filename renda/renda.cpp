#ifndef UNICODE
#define UNICODE
#endif 

#include <no_sal2.h>
#include <windows.h>
#include <wchar.h>

#include "GlobalVariants.h"
#include "WindowManager.h"


// 関数宣言-------------------------
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void SendRightClick();
void StopRenda();
void StartRenda();
DWORD WINAPI RendaThreadProc(LPVOID lpPram);
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

// キーを押したときの処理
// LowLevelKeyboardProc()のほうに処理書いてるかもしれないので注意

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);

                // All painting occurs here, between BeginPaint and EndPaint.

                FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

                EndPaint(hwnd, &ps);
            }
            return 0;

        case WM_COMMAND:
            if (LOWORD(wParam) == ID_BTN_START && !isRunning)
            {
                // UI切り替え
				StartRenda();
                return 0;
            }

            if (LOWORD(wParam) == ID_BTN_STOP && isRunning)
            {
				// UI切り替え
				StopRenda();
				return 0;
            }

			// ComboBoxの選択が変わったときの処理
            if (HIWORD(wParam) == CBN_SELCHANGE && (HWND)lParam == hComboBox)
            {
                int sel = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
                SendMessage(hComboBox, CB_GETLBTEXT, sel, (LPARAM)Button_StartAndStop);
				Button_StartAndStop[CHAR_SIZE - 1] = L'\0'; // 念のため終端を確保
                // MessageBox(hwnd, Button_StartAndStop, L"選択された項目", MB_OK);
                return 0;
            }
            
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// 動作面の実装-----------------------

void StartRenda()
{
    isRunning = true;
    GetWindowText(hEditInput, Input_Interval, 32);
    Interval = _wtoi(Input_Interval); // 入力値を数値に変換してセット
	RefreshMainWindow();

    hRendaThread = CreateThread(NULL, 0, RendaThreadProc, NULL, 0, NULL);
	// StartKeyHook();
}

void StopRenda()
{
    isRunning = false;
    if (hRendaThread)
    {
        WaitForSingleObject(hRendaThread, INFINITE);
        CloseHandle(hRendaThread);
        hRendaThread = NULL;
    }
	RefreshMainWindow();
    // StopKeyHook();
}

void SendRightClick()
{
    INPUT input[2] = {};

    // 右ボタン押下
    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    // 右ボタン離す
    input[1].type = INPUT_MOUSE;
    input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    SendInput(2, input, sizeof(INPUT));
}

// ループ処理実装のための環境-----------------------
// startRenda(), stopRenda() で呼んでいるThreadはこちらで定義

DWORD WINAPI RendaThreadProc(LPVOID lpPram)
{
    while (isRunning)
    {
        SendRightClick();
        Sleep(Interval);
    }
    return 0;
}

// 他アプリを起動中でも動作する環境-----------------------
// 他アプリ実行中でもCALLBACK内が動作するため、キーを押したときの処理はこっちに描くこともある
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) 
{
    if (nCode == HC_ACTION)
    {
        KBDLLHOOKSTRUCT* pKbd = (KBDLLHOOKSTRUCT*)lParam;
        if (wParam == WM_KEYDOWN)
        {
            // コンボボックス選択値に応じてキー判定
            if (isRunning)
            {
                if (wcscmp(Button_StartAndStop, L"Insert") == 0 && pKbd->vkCode == VK_INSERT)
                {
                    StopRenda();
                }
                else if (wcscmp(Button_StartAndStop, L"Home") == 0 && pKbd->vkCode == VK_HOME)
                {
                    StopRenda();
                }
                else if (wcscmp(Button_StartAndStop, L"PageUp") == 0 && pKbd->vkCode == VK_PRIOR)
                {
                    StopRenda();
                }
                else if (wcscmp(Button_StartAndStop, L"Delete") == 0 && pKbd->vkCode == VK_DELETE)
                {
                    StopRenda();
                }
                else if (wcscmp(Button_StartAndStop, L"End") == 0 && pKbd->vkCode == VK_END)
                {
                    StopRenda();
                }
                else if (wcscmp(Button_StartAndStop, L"PageDown") == 0 && pKbd->vkCode == VK_NEXT)
                {
                    StopRenda();
                }
            }
            else
            {
                if (wcscmp(Button_StartAndStop, L"Insert") == 0 && pKbd->vkCode == VK_INSERT)
                {
                    StartRenda();
                }
                else if (wcscmp(Button_StartAndStop, L"Home") == 0 && pKbd->vkCode == VK_HOME)
                {
                    StartRenda();
                }
                else if (wcscmp(Button_StartAndStop, L"PageUp") == 0 && pKbd->vkCode == VK_PRIOR)
                {
                    StartRenda();
                }
                else if (wcscmp(Button_StartAndStop, L"Delete") == 0 && pKbd->vkCode == VK_DELETE)
                {
                    StartRenda();
                }
                else if (wcscmp(Button_StartAndStop, L"End") == 0 && pKbd->vkCode == VK_END)
                {
                    StartRenda();
                }
                else if (wcscmp(Button_StartAndStop, L"PageDown") == 0 && pKbd->vkCode == VK_NEXT)
                {
                    StartRenda();
                }
            }
        }
    }
    return CallNextHookEx(g_hKeyHook, nCode, wParam, lParam);
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