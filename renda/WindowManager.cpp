#include "WindowManager.h"

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