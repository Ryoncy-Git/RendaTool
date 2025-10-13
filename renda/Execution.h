#pragma once

#include <wchar.h>
#include <windows.h>

#include "GlobalVariants.h"
#include "WindowManager.h"

void StartRenda();
void StopRenda();
void SendRightClick();
DWORD WINAPI RendaThreadProc(LPVOID lpPram);