#include "GlobalVariants.h"


bool isRunning = false;
wchar_t InputInterval[CHAR_SIZE] = L"100"; // 連打間隔の初期値（ミリ秒）
int Interval = 100;
wchar_t ButtonStartAndStop[CHAR_SIZE] = L"Insert"; // ボタン名の初期値
wchar_t rendaKey[CHAR_SIZE] = L"Left Click";


HWND hBtnStart = NULL;
HWND hBtnStop = NULL;
HWND hTextIntervalLabel = NULL;
HWND hTextInterval = NULL;
HWND hTextSSLabel = NULL;
HWND hTextSS = NULL; // Start and Stop
HWND hTextrendaKeyLabel = NULL;
HWND hTextrendaKey = NULL;
HWND hComboInputType = NULL;

HINSTANCE g_hInstance = NULL;

HANDLE hRendaThread = NULL;
HHOOK g_hKeyHook = NULL;

HWND hInputInterval = NULL; // ユーザーが連打間隔を入力するウィンドウ（Edit）
HWND hComboSSButtonType = NULL; // ユーザーが開始・停止ボタンのタイプを選択するウィンドウ（ComboBox）

// ~~Labelって名前のやつはその説明のためのウィンドウ（待機中に入力欄の上に表示する）
