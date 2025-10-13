#include "Execution.h"	

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

DWORD WINAPI RendaThreadProc(LPVOID lpPram)
{
    while (isRunning)
    {
        SendRightClick();
        Sleep(Interval);
    }
    return 0;
}