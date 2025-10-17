#pragma once

#include <wchar.h>
#include <windows.h>

#include "GlobalVariants.h"
#include "WindowManager.h"
#include "Output.h"

void StartRenda();
void StopRenda();
DWORD WINAPI RendaThreadProc(LPVOID lpPram);
WORD GetVkCodeFromLabel(const wchar_t* label);			