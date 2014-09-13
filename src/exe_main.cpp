#include <iostream>
#include <string>
#include <windows.h>

#include "dll_main.h"

#ifdef _DEBUG
#define SNU_MODULE_NAME L"SNU_d.dll"
#else
#define SNU_MODULE_NAME L"SNU.dll"
#endif

#define SNU_DUMMY_WND_CLASS L"SnuDummyWndClass"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// We need to initialize the SNU.dll module first, since we rely on its settings object here.
	HMODULE snuModule = LoadLibrary(SNU_MODULE_NAME);

	//Next we fill out all the settings required to start the actual Skype app.
	SHELLEXECUTEINFO execInfo = {0};
	execInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	execInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	execInfo.lpParameters = L"";
	execInfo.lpDirectory = nullptr;
	execInfo.lpVerb = L"open";
	execInfo.hwnd = NULL;
	execInfo.nShow = SW_SHOWDEFAULT;

	wchar_t* skypeAppName = new wchar_t[MAX_PATH];
	GetPrivateProfileString(L"SNU", L"app", L"Skype.exe", skypeAppName, MAX_PATH,
							settings.iniPath.c_str());
	execInfo.lpFile = skypeAppName;

	if (!ShellExecuteEx(&execInfo))
		return -1;

	delete skypeAppName;

	DWORD skypeProcID = GetProcessId(execInfo.hProcess);
	HWINEVENTHOOK snuHook = SetWinEventHook(EVENT_OBJECT_LOCATIONCHANGE,
											EVENT_OBJECT_LOCATIONCHANGE, snuModule,
											notificationHook, skypeProcID, NULL,
											WINEVENT_INCONTEXT | WINEVENT_SKIPOWNPROCESS);

	MSG msg;
	// Set timer every second to force message loop to run (required so SNU realizes when Skype
	// has been closed and does not continue uselessly running in the background).
	UINT_PTR timer = SetTimer(NULL, NULL, 1000, nullptr);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_TIMER)
		{
			DWORD exitCode = 0;
			if (!GetExitCodeProcess(execInfo.hProcess, &exitCode)
				|| exitCode != STILL_ACTIVE)
				break;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	KillTimer(NULL, timer);

	return 0;
}
