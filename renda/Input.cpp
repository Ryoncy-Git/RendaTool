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

    case WM_COMMAND:
        if (LOWORD(wParam) == ID_BTN_START && !isRunning)
        {
            // UI�؂�ւ�
            StartRenda();
            return 0;
        }

        if (LOWORD(wParam) == ID_BTN_STOP && isRunning)
        {
            // UI�؂�ւ�
            StopRenda();
            return 0;
        }

        // ComboBox�̑I�����ς�����Ƃ��̏���
        if (HIWORD(wParam) == CBN_SELCHANGE && (HWND)lParam == hComboBox)
        {
            int sel = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
            SendMessage(hComboBox, CB_GETLBTEXT, sel, (LPARAM)Button_StartAndStop);
            Button_StartAndStop[CHAR_SIZE - 1] = L'\0'; // �O�̂��ߏI�[���m��
            // MessageBox(hwnd, Button_StartAndStop, L"�I�����ꂽ����", MB_OK);
            return 0;
        }

        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


// ���A�v�����N�����ł����삷���-----------------------
// ���A�v�����s���ł�CALLBACK�������삷�邽�߁A�L�[���������Ƃ��̏����͂������ɕ`�����Ƃ�����
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        KBDLLHOOKSTRUCT* pKbd = (KBDLLHOOKSTRUCT*)lParam;
        if (wParam == WM_KEYDOWN)
        {
            // �R���{�{�b�N�X�I��l�ɉ����ăL�[����
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