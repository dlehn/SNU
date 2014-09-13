#ifndef DLL_MAIN_H
#define DLL_MAIN_H

#include <Windows.h>
#include <string>

#include "dll_export.h"

enum ScreenCorner
{
	TopLeft = 0,
	TopRight,
	BottomRight,
	BottomLeft
};

struct SkypeHookSettings
{
	std::wstring iniPath;
	unsigned monitor;
	ScreenCorner corner;
	POINT offset;
};

// Settings object for the hook DLL, also used to communicate with SNU.exe.
SNU_PUBLIC extern SkypeHookSettings settings;

// The event hook to be attached to Skype's window resize events.
SNU_PUBLIC void APIENTRY notificationHook(HWINEVENTHOOK hWinEventHook, DWORD event, HWND hwnd,
										  LONG idObject, LONG idChild, DWORD idEventThread,
										  DWORD dwmsEventTime);

// The DLL's entry function, used to load settings.
SNU_PUBLIC BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved);

#endif