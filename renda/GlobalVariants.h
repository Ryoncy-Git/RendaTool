#pragma once
#include <windows.h>
#include <wchar.h>

// ÉOÉçÅ[ÉoÉãïœêî
#define ID_BTN_START 1001
#define ID_BTN_STOP  1002
#define ID_BTN_WIN1  1101
#define ID_BTN_WIN2  1102
#define CHAR_SIZE 32

extern bool isRunning;
extern wchar_t Input_Interval[32];
extern int Interval;
extern wchar_t Button_StartAndStop[32];

extern HWND hBtnStart;
extern HWND hBtnStop;
extern HWND hTextRunning;
extern HWND hEditInput;
extern HWND hComboBox;

extern HINSTANCE g_hInstance;
extern HANDLE hRendaThread;
extern HHOOK g_hKeyHook;