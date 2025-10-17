#include "Execution.h"	
#include "Output.h"

HANDLE hStopEvent;

void StartRenda()
{
    isRunning = true;
    GetWindowText(hInputInterval, InputInterval, 32);
    Interval = _wtoi(InputInterval); // 入力値を数値に変換してセット
    RefreshMainWindow();

    hRendaThread = CreateThread(NULL, 0, RendaThreadProc, NULL, 0, NULL);
    hStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL); // 手動リセット、非シグナル状態
    // StartKeyHook();
}

void StopRenda()
{
    isRunning = false;
    if (hStopEvent)
        SetEvent(hStopEvent); // スレッドに終了を通知


    if (hRendaThread)
    {
        WaitForSingleObject(hRendaThread, INFINITE);
        CloseHandle(hRendaThread);
        hRendaThread = NULL;
    }

    if (hStopEvent)
    {
        CloseHandle(hStopEvent);
        hStopEvent = NULL;
    }

    RefreshMainWindow();
    // StopKeyHook();
}

DWORD WINAPI RendaThreadProc(LPVOID lpPram)
{
    if (wcsstr(rendaKey, L"Left Click") != nullptr)
    {
        while (isRunning)
        {
            SendLeftClick();
            if (WaitForSingleObject(hStopEvent, Interval) == WAIT_OBJECT_0)
                break;
        }
    }
    else if (wcsstr(rendaKey, L"Right Click") != nullptr)
    {
        while (isRunning)
        {
            SendRightClick();
            if (WaitForSingleObject(hStopEvent, Interval) == WAIT_OBJECT_0)
                break;
        }
    }
    else if (wcsstr(rendaKey, L"Middle Click") != nullptr)
    {
        while (isRunning)
        {
            SendMiddleClick();
            if (WaitForSingleObject(hStopEvent, Interval) == WAIT_OBJECT_0)
                break;
        }
	}
    else
    {
		WORD vkCode = GetVkCodeFromLabel(rendaKey);

        while (isRunning)
        {
            SendKeyPress(vkCode);
            if (WaitForSingleObject(hStopEvent, Interval) == WAIT_OBJECT_0)
                break;
        }
    }

    return 0;
}

WORD GetVkCodeFromLabel(const wchar_t* label)
{
    if (wcsncmp(label, L"Key ", 4) == 0) {
        wchar_t ch = label[4];
        if (ch >= L'A' && ch <= L'Z') {
            return static_cast<WORD>(ch); // ASCII → VK_A〜VK_Z
        }
    }
    if (wcscmp(label, L"Key Esc") == 0)         return VK_ESCAPE;
    if (wcscmp(label, L"Key Tab") == 0)         return VK_TAB;
    if (wcscmp(label, L"Key CapsLock") == 0)    return VK_CAPITAL;
    if (wcscmp(label, L"Key Left Shift") == 0)  return VK_LSHIFT;
    if (wcscmp(label, L"Key Left Ctrl") == 0)   return VK_LCONTROL;
    if (wcscmp(label, L"Key Left Alt") == 0)    return VK_LMENU;
    if (wcscmp(label, L"Key Right Alt") == 0)   return VK_RMENU;
    if (wcscmp(label, L"Key Right Shift") == 0) return VK_RSHIFT;
    if (wcscmp(label, L"Key Right Ctrl") == 0)  return VK_RCONTROL;
    if (wcscmp(label, L"Key Enter") == 0)       return VK_RETURN;
    if (wcscmp(label, L"Key Space") == 0)       return VK_SPACE;

    return 0;
}