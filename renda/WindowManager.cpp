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

    hComboInputType = CreateWindow(
        L"COMBOBOX",            // �� �R���{�{�b�N�X�R���g���[��
        L"Insert",                   // �����l�i�󕶎���j
        WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, // �h���b�v�_�E�����X�g�X�^�C��
        50, 300, 200, 300,      // x, y, ��, ����
        hwnd,                   // �e�E�B���h�E
        NULL,                   // �R���g���[��ID�i�K�v�Ȃ� (HMENU)ID_COMBOBOX �Ȃǁj
        hInstance,
        NULL
    );
    SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Right Click");
    SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Left Click");
    SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Middle Click");
    SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key A");
    SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key B");
    SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key C");
	SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key D");
	SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key E");
	SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key F");
	SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key G");
	SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key H");
	SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key I");
	SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key J");
	SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key K");
	SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key L");
	SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key M");
	SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key N");
	SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key O");
	SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key P");
	SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key Q");
	SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key R");
	SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key S");
	SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key T");
	SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key U");
	SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key V");
	SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key W");
	SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key X");
	SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key Y");
	SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key Z");
    SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key Esc");
    SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key Tab");
    SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key CapsLock");
    SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key Left Shift");
    SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key Left Ctrl");
    SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key Left Alt");
    SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key Right Alt");
    SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key Right Shift");
    SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key Right Ctrl");
    SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key Enter");
    SendMessage(hComboInputType, CB_ADDSTRING, 0, (LPARAM)L"Key Space");
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