#include "WindowManager.h"

void CreateMainWindow(HWND hwnd, _In_ HINSTANCE hInstance)
{
    hBtnStart = CreateWindow(
        L"BUTTON",
        L"�J�n",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        50, 50, 120, 40,
        hwnd,
        (HMENU)ID_BTN_START,
        hInstance,
        NULL
    );

    hEditInput = CreateWindow(
        L"EDIT",                // �� �G�f�B�b�g�R���g���[��
        Input_Interval,         // �����l�i�󕶎���j
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
        50, 100, 120, 25,       // x, y, ��, ����
        hwnd,                   // �e�E�B���h�E
        NULL,                   // �R���g���[��ID�i�K�v�Ȃ� (HMENU)ID_EDIT_INPUT �Ȃǁj
        hInstance,
        NULL
    );
    GetWindowText(hEditInput, Input_Interval, 32); // �����l���Z�b�g

    hBtnStop = CreateWindow(
        L"BUTTON",
        L"��~",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        50, 50, 120, 40,
        hwnd,
        (HMENU)ID_BTN_STOP,
        hInstance,
        NULL
    );

    wchar_t text[32];
    swprintf(text, CHAR_SIZE, L"�A�ŊԊu %d", Interval);
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
        L"COMBOBOX",            // �� �R���{�{�b�N�X�R���g���[��
        L"Insert",                   // �����l�i�󕶎���j
        WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, // �h���b�v�_�E�����X�g�X�^�C��
        50, 150, 120, 200,      // x, y, ��, ����
        hwnd,                   // �e�E�B���h�E
        NULL,                   // �R���g���[��ID�i�K�v�Ȃ� (HMENU)ID_COMBOBOX �Ȃǁj
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
        MessageBox(NULL, L"Window�̍\���v�f���s���̏�ԂŃ��t���b�V�����܂���", L"���", MB_OK | MB_ICONINFORMATION);
        return;
    }

    if (isRunning)
    {
        ShowWindow(hBtnStart, SW_HIDE);
        ShowWindow(hBtnStop, SW_SHOW);
        ShowWindow(hEditInput, SW_HIDE);
        ShowWindow(hTextRunning, SW_SHOW);

        wchar_t text[CHAR_SIZE];
        swprintf(text, CHAR_SIZE, L"�A�ŊԊu %d", Interval);
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