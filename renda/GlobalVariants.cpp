#include "GlobalVariants.h"


bool isRunning = false;
wchar_t InputInterval[CHAR_SIZE] = L"100"; // �A�ŊԊu�̏����l�i�~���b�j
int Interval = 100;
wchar_t ButtonStartAndStop[CHAR_SIZE] = L"Insert"; // �{�^�����̏����l
wchar_t rendaKey[CHAR_SIZE] = L"Left Click";


HWND hBtnStart = NULL;
HWND hBtnStop = NULL;
HWND hTextIntervalLabel = NULL;
HWND hTextInterval = NULL;
HWND hTextSSLabel = NULL;
HWND hTextSS = NULL; // Start and Stop
HWND hTextrendaKeyLabel = NULL;
HWND hTextrendaKey = NULL;
HWND hComboInputType = NULL;

HINSTANCE g_hInstance = NULL;

HANDLE hRendaThread = NULL;
HHOOK g_hKeyHook = NULL;

HWND hInputInterval = NULL; // ���[�U�[���A�ŊԊu����͂���E�B���h�E�iEdit�j
HWND hComboSSButtonType = NULL; // ���[�U�[���J�n�E��~�{�^���̃^�C�v��I������E�B���h�E�iComboBox�j

// ~~Label���Ė��O�̂�͂��̐����̂��߂̃E�B���h�E�i�ҋ@���ɓ��͗��̏�ɕ\������j
