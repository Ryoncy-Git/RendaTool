#include "GlobalVariants.h"


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