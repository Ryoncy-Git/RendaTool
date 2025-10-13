#include "Output.h"

void SendRightClick()
{
    INPUT input[2] = {};

    // �E�{�^������
    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    // �E�{�^������
    input[1].type = INPUT_MOUSE;
    input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    SendInput(2, input, sizeof(INPUT));
}

void SendLeftClick()
{
    INPUT input[2] = {};

    // ���{�^������
    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

    // ���{�^������
    input[1].type = INPUT_MOUSE;
    input[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;

    SendInput(2, input, sizeof(INPUT));
}

void SendMiddleClick()
{
    INPUT input[2] = {};

    // ���{�^������
    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;

    // ���{�^������
    input[1].type = INPUT_MOUSE;
    input[1].mi.dwFlags = MOUSEEVENTF_MIDDLEUP;

	SendInput(2, input, sizeof(INPUT));
}

void SendKey(WORD vkCode)
{
    INPUT input[2] = {};

    // �L�[����
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = vkCode;

    // �L�[����
    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = vkCode;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(2, input, sizeof(INPUT));
}