#include "Input.h"
#include "GlobalVariants.h"
#include "Execution.h"

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

    case WM_MOUSEWHEEL:
    {
        POINT pt;                   
        GetCursorPos(&pt);
        // HWND hTarget = WindowFromPoint(pt);
		HWND hTarget = hComboInputType;
		
        /*COMBOBOXINFO cbi = { sizeof(COMBOBOXINFO) };
        GetComboBoxInfo(hComboInputType, &cbi);*/

        if (hTarget == hComboInputType /* || hTatget == hwnd || hTarget == cbi.hwndList*/) {
            // スクロール処理を実行
            int delta = GET_WHEEL_DELTA_WPARAM(wParam); 
            int curSel = SendMessage(hTarget, CB_GETCURSEL, 0, 0);
            int count = SendMessage(hTarget, CB_GETCOUNT, 0, 0);
            if (curSel == CB_ERR) curSel = 0;
            if (delta > 0 && curSel > 0) curSel--;
            else if (delta < 0 && curSel < count - 1) curSel++;
            SendMessage(hTarget, CB_SETCURSEL, curSel, 0);
            break;
        }
    }

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
        if (HIWORD(wParam) == CBN_SELCHANGE && (HWND)lParam == hComboSSButtonType)
        {
            int sel = SendMessage(hComboSSButtonType, CB_GETCURSEL, 0, 0);
            SendMessage(hComboSSButtonType, CB_GETLBTEXT, sel, (LPARAM)ButtonStartAndStop);
            ButtonStartAndStop[CHAR_SIZE - 1] = L'\0'; // 念のため終端を確保
            // MessageBox(hwnd, Button_StartAndStop, L"選択された項目", MB_OK);
            return 0;
        }

        if (HIWORD(wParam) == CBN_SELCHANGE && (HWND)lParam == hComboInputType)
        {
            int sel = SendMessage(hComboInputType, CB_GETCURSEL, 0, 0);
            SendMessage(hComboInputType, CB_GETLBTEXT, sel, (LPARAM)rendaKey);
            rendaKey[CHAR_SIZE - 1] = L'\0'; // 念のため終端を確保
            // MessageBox(hwnd, rendaKey, L"選択された項目", MB_OK);
            return 0;
        }

        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
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
                if (wcscmp(ButtonStartAndStop, L"Insert") == 0 && pKbd->vkCode == VK_INSERT)
                {
                    StopRenda();
                }
                else if (wcscmp(ButtonStartAndStop, L"Home") == 0 && pKbd->vkCode == VK_HOME)
                {
                    StopRenda();
                }
                else if (wcscmp(ButtonStartAndStop, L"PageUp") == 0 && pKbd->vkCode == VK_PRIOR)
                {
                    StopRenda();
                }
                else if (wcscmp(ButtonStartAndStop, L"Delete") == 0 && pKbd->vkCode == VK_DELETE)
                {
                    StopRenda();
                }
                else if (wcscmp(ButtonStartAndStop, L"End") == 0 && pKbd->vkCode == VK_END)
                {
                    StopRenda();
                }
                else if (wcscmp(ButtonStartAndStop, L"PageDown") == 0 && pKbd->vkCode == VK_NEXT)
                {
                    StopRenda();
                }
            }
            else
            {
                if (wcscmp(ButtonStartAndStop, L"Insert") == 0 && pKbd->vkCode == VK_INSERT)
                {
                    StartRenda();
                }
                else if (wcscmp(ButtonStartAndStop, L"Home") == 0 && pKbd->vkCode == VK_HOME)
                {
                    StartRenda();
                }
                else if (wcscmp(ButtonStartAndStop, L"PageUp") == 0 && pKbd->vkCode == VK_PRIOR)
                {
                    StartRenda();
                }
                else if (wcscmp(ButtonStartAndStop, L"Delete") == 0 && pKbd->vkCode == VK_DELETE)
                {
                    StartRenda();
                }
                else if (wcscmp(ButtonStartAndStop, L"End") == 0 && pKbd->vkCode == VK_END)
                {
                    StartRenda();
                }
                else if (wcscmp(ButtonStartAndStop, L"PageDown") == 0 && pKbd->vkCode == VK_NEXT)
                {
                    StartRenda();
                }
            }
        }
    }
    return CallNextHookEx(g_hKeyHook, nCode, wParam, lParam);
}