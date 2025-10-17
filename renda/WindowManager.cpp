#include "WindowManager.h"

void CreateMainWindow(HWND hwnd, _In_ HINSTANCE hInstance)
{
	CreateUIInRunning(hwnd, hInstance);
	CreateUIInWaiting(hwnd, hInstance);
}

void RefreshMainWindow()
{
    if (isRunning)
    {
		ShowUIInRunning();

        wchar_t text[CHAR_SIZE];
        swprintf(text, CHAR_SIZE, L"�A�ŊԊu\n%d (ms)", Interval);
        SetWindowText(hTextInterval, text);    

		swprintf(text, CHAR_SIZE, L"�J�n�A�I���L�[\n%s", ButtonStartAndStop);
		SetWindowText(hTextSS, text);

		swprintf(text, CHAR_SIZE, L"�A�ł���L�[\n%s", rendaKey);
		SetWindowText(hTextrendaKey, text);
    }
    else
    {
		ShowUIInWaiting();
    }
}

void CreateUIInRunning(HWND hwnd, _In_ HINSTANCE hInstance)
{
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
    swprintf(text, CHAR_SIZE, L"�A�ŊԊu\n%d (ms)", Interval);
    hTextInterval = CreateWindow(
        L"STATIC",
        text,
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        50, 110, 120, 40,
        hwnd,
        NULL,
        hInstance,
        NULL
    );

    swprintf(text, CHAR_SIZE, L"SSButton\n%s", ButtonStartAndStop);
    hTextSS = CreateWindow(
        L"STATIC",
        text,
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        50, 190, 120, 40,
        hwnd,
        NULL,
        hInstance,
        NULL
    );

    swprintf(text, CHAR_SIZE, L"rendaKey\n%s", rendaKey);
    hTextrendaKey = CreateWindow(
        L"STATIC",
        text,
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        50, 270, 120, 40,
        hwnd,
        NULL,
        hInstance,
        NULL
    );
}

void CreateUIInWaiting(HWND hwnd, _In_ HINSTANCE hInstance)
{
	hBtnStart = CreateWindow( // �J�n�{�^���̍쐬
        L"BUTTON",
        L"�J�n",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        50, 50, 120, 40,
        hwnd,
        (HMENU)ID_BTN_START,
        hInstance,
        NULL
    );

	hInputInterval = CreateWindow( // �A�ŊԊu���͗��̍쐬
        L"EDIT",             
        InputInterval,       
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
        50, 131, 120, 25,       
        hwnd,                   
        NULL,                   
        hInstance,
        NULL
    );
    GetWindowText(hInputInterval, InputInterval, 32); // �����l���Z�b�g

    wchar_t text[32];
    swprintf(text, CHAR_SIZE, L"�A�ŊԊu(ms)");
	hTextIntervalLabel = CreateWindow( // �A�ŊԊu���x���̍쐬
        L"STATIC",
        text,
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        50, 110, 120, 20,
        hwnd,
        NULL,
        hInstance,
        NULL
    );

    swprintf(text, CHAR_SIZE, L"�J�n�A�I���L�[");
    hTextSSLabel = CreateWindow( // �J�n�A�I���L�[���x���̍쐬
        L"STATIC",
        text,
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        50, 165, 120, 25,
        hwnd,
        NULL,
        hInstance,
        NULL
    );

    swprintf(text, CHAR_SIZE, L"�A�ł���L�[");
	hTextrendaKeyLabel = CreateWindow( // �A�ł���L�[���x���̍쐬
        L"STATIC",
        text,
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        50, 225, 120, 25,
        hwnd,
        NULL,
        hInstance,
        NULL
    );


    hComboSSButtonType = CreateWindow(
        L"COMBOBOX",            // �� �R���{�{�b�N�X�R���g���[��
        L"Insert",                   // �����l�i�󕶎���j
        WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, // �h���b�v�_�E�����X�g�X�^�C��
        50, 190, 120, 200,      // x, y, ��, ����
        hwnd,                   // �e�E�B���h�E
        NULL,                   // �R���g���[��ID�i�K�v�Ȃ� (HMENU)ID_COMBOBOX �Ȃǁj
        hInstance,
        NULL
    );
    SendMessage(hComboSSButtonType, CB_ADDSTRING, 0, (LPARAM)L"Insert");
    SendMessage(hComboSSButtonType, CB_ADDSTRING, 0, (LPARAM)L"Home");
    SendMessage(hComboSSButtonType, CB_ADDSTRING, 0, (LPARAM)L"PageUp");
    SendMessage(hComboSSButtonType, CB_ADDSTRING, 0, (LPARAM)L"Delete");
    SendMessage(hComboSSButtonType, CB_ADDSTRING, 0, (LPARAM)L"End");
    SendMessage(hComboSSButtonType, CB_ADDSTRING, 0, (LPARAM)L"PageDown");

    hComboInputType = CreateWindow(
        L"COMBOBOX",            // �� �R���{�{�b�N�X�R���g���[��
        L"Insert",                   // �����l�i�󕶎���j
        WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, // �h���b�v�_�E�����X�g�X�^�C��
        50, 250, 120, 200,      // x, y, ��, ����
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

void ShowUIInRunning()
{
	ShowWindow(hBtnStop, SW_SHOW);
	ShowWindow(hTextInterval, SW_SHOW);
	ShowWindow(hTextSS, SW_SHOW);           
	ShowWindow(hTextrendaKey, SW_SHOW);

    ShowWindow(hComboInputType, SW_HIDE);
    ShowWindow(hComboSSButtonType, SW_HIDE);
    ShowWindow(hBtnStart, SW_HIDE);
    ShowWindow(hInputInterval, SW_HIDE);
    ShowWindow(hTextIntervalLabel, SW_HIDE);
    ShowWindow(hTextSSLabel, SW_HIDE);
    ShowWindow(hTextrendaKeyLabel, SW_HIDE);
}

void ShowUIInWaiting()
{
    ShowWindow(hBtnStop, SW_HIDE);
    ShowWindow(hTextInterval, SW_HIDE);
    ShowWindow(hTextSS, SW_HIDE);
    ShowWindow(hTextrendaKey, SW_HIDE);

    ShowWindow(hComboInputType, SW_SHOW);
    ShowWindow(hComboSSButtonType, SW_SHOW);
    ShowWindow(hBtnStart, SW_SHOW);
    ShowWindow(hInputInterval, SW_SHOW);
    ShowWindow(hTextIntervalLabel, SW_SHOW);
    ShowWindow(hTextSSLabel, SW_SHOW);
    ShowWindow(hTextrendaKeyLabel, SW_SHOW);
}