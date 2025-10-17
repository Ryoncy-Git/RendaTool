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
extern wchar_t InputInterval[32];
extern int Interval;
extern wchar_t ButtonStartAndStop[32];
extern wchar_t rendaKey[32];

extern HWND hBtnStart;
extern HWND hBtnStop;
extern HWND hTextIntervalLabel;
extern HWND hTextInterval;
extern HWND hTextSSLabel;
extern HWND hTextSS; // Start and Stop
extern HWND hTextrendaKeyLabel;
extern HWND hTextrendaKey;
extern HWND hComboInputType;
extern HWND hComboSSButtonType;
extern HWND hInputInterval;

extern HINSTANCE g_hInstance;
extern HANDLE hRendaThread;
extern HHOOK g_hKeyHook;
