// 実装したい機能
// キーボード含めて自動的に操作できるようにしたい
// // キーコードを調べれば何とかなりそう
// 特定のストリーム(一連の流れ)を作りたい
// // 例えば、Aボタンを押して、Bボタンを押して、Cボタンを押す、みたいな
// // 可変配列を使いたい

#ifndef UNICODE
#define UNICODE
#endif 

#include <no_sal2.h>
#include <windows.h>
#include <wchar.h>

// グローバル変数
#define ID_BTN_START 1001
#define ID_BTN_STOP  1002
#define ID_BTN_WIN1  1101
#define ID_BTN_WIN2  1102
#define CHAR_SIZE 32


bool isRunning = false;
wchar_t Input_Interval[CHAR_SIZE] = L"100"; // 連打間隔の初期値（ミリ秒）
int Interval = 100;
wchar_t Button_StartAndStop[CHAR_SIZE] = L"Button"; // ボタン名の初期値


HWND hBtnStart = NULL;
HWND hBtnStop = NULL;
HWND hTextRunning = NULL;
HWND hEditInput = NULL;
HWND hComboBox = NULL;

HINSTANCE g_hInstance = NULL;

HANDLE hRendaThread = NULL;
HHOOK g_hKeyHook = NULL;


// 関数宣言
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void SendRightClick();
void StopRenda();
void StartRenda();
DWORD WINAPI RendaThreadProc(LPVOID lpPram);
void StartKeyHook();
void StopKeyHook();
void CreateMainWindow(HWND hwnd, _In_ HINSTANCE hInstance);
void RefreshMainWindow();




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

// 新しい法のウィンドウ案
void CreateMainWindow(HWND hwnd, _In_ HINSTANCE hInstance)
{
    hBtnStart = CreateWindow(
        L"BUTTON",
        L"開始",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        50, 50, 120, 40,
        hwnd,
        (HMENU)ID_BTN_START,
        hInstance,
        NULL
    );

    hEditInput = CreateWindow(
        L"EDIT",                // ← エディットコントロール
        Input_Interval,         // 初期値（空文字列）
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
        50, 100, 120, 25,       // x, y, 幅, 高さ
        hwnd,                   // 親ウィンドウ
        NULL,                   // コントロールID（必要なら (HMENU)ID_EDIT_INPUT など）
        hInstance,
        NULL
    );
    GetWindowText(hEditInput, Input_Interval, 32); // 初期値をセット
                    
    hBtnStop = CreateWindow(
        L"BUTTON",
        L"停止",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        50, 50, 120, 40,
        hwnd,
        (HMENU)ID_BTN_STOP,
        hInstance,
        NULL
    );

    wchar_t text[32];
    swprintf(text, CHAR_SIZE, L"連打間隔 %d", Interval);
    hTextRunning = CreateWindow(
        L"STATIC",
        text,
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        50, 100, 120, 25,
        hwnd,
        NULL,
        hInstance,
        NULL
    );

    hComboBox = CreateWindow(
        L"COMBOBOX",            // ← コンボボックスコントロール
        L"Insert",                   // 初期値（空文字列）
        WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, // ドロップダウンリストスタイル
        50, 150, 120, 200,      // x, y, 幅, 高さ
        hwnd,                   // 親ウィンドウ
        NULL,                   // コントロールID（必要なら (HMENU)ID_COMBOBOX など）
        hInstance,
        NULL
	);
    SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)L"Insert");
	SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)L"Home");
	SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)L"PageUp");
	SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)L"Delete");
	SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)L"End");
	SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)L"PageDown");
}

void RefreshMainWindow()
{
    if (!(hBtnStart && hBtnStop && hTextRunning && hEditInput))
    {
        MessageBox(NULL, L"Windowの構成要素が不足の状態でリフレッシュしました", L"情報", MB_OK | MB_ICONINFORMATION); 
        return;
    }

    if (isRunning)
    {
        ShowWindow(hBtnStart, SW_HIDE);
        ShowWindow(hBtnStop, SW_SHOW);
        ShowWindow(hEditInput, SW_HIDE);
        ShowWindow(hTextRunning, SW_SHOW);

        wchar_t text[CHAR_SIZE];
        swprintf(text, CHAR_SIZE, L"連打間隔 %d", Interval);
        SetWindowText(hTextRunning, text);
    }
    else
    {
        ShowWindow(hBtnStart, SW_SHOW);
        ShowWindow(hBtnStop, SW_HIDE);
        ShowWindow(hEditInput, SW_SHOW);
        ShowWindow(hTextRunning, SW_HIDE);
	}
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