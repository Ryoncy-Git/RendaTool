#pragma once

#include <Windows.h>
#include <wchar.h>
#include "GlobalVariants.h"

void SendRightClick();
void SendLeftClick();
void SendMiddleClick();

void SendKeyPress(WORD vkCode);