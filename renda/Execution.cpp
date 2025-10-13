#include "Execution.h"	
#include "Output.h"

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

DWORD WINAPI RendaThreadProc(LPVOID lpPram)
{
    while (isRunning)
    {
        SendRightClick();
        Sleep(Interval);
    }
    return 0;
}