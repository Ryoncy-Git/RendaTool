#pragma once

#include "GlobalVariants.h"
#include <windows.h>
#include <wchar.h>

void CreateMainWindow(HWND hwnd, _In_ HINSTANCE hInstance);
// Refresh the main window to reflect changes in global values

void RefreshMainWindow();
// Update the window title based on the current file name and unsaved changes