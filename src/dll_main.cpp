#include "dll_main.h"

struct MonitorEnumData
{
	std::wstring devName;
	RECT workArea;
};

SkypeHookSettings settings;

std::wstring getWorkingDirectory()
{
	wchar_t buffer[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, buffer);
	return buffer;
}

BOOL CALLBACK enumMonitorProc(HMONITOR monitor, HDC hdc, LPRECT rect, LPARAM param)
{
	MonitorEnumData *data = (MonitorEnumData*)param;
	
	MONITORINFOEX info;
	info.cbSize = sizeof(MONITORINFOEX);

	if (GetMonitorInfo(monitor, &info))
		data->workArea = info.rcWork;
	else
		return TRUE;

	return info.szDevice != data->devName;
}

// Get the work area coordinates of the monitor on which we want to display the popup.
RECT getMonitorWorkArea(unsigned index)
{
	DISPLAY_DEVICE device = {0};
	device.cb = sizeof(DISPLAY_DEVICE);
	
	if (!EnumDisplayDevices(nullptr, index, &device, EDD_GET_DEVICE_INTERFACE_NAME))
		return RECT();

	MonitorEnumData data;
	data.devName = device.DeviceName;

	EnumDisplayMonitors(NULL, NULL, enumMonitorProc, (LPARAM)&data);

	return data.workArea;
}

// This function calculates an appropriate position for the notification popup based on the 
// configuration file SNU.ini.
POINT calcWindowPos(const RECT& _base)
{
	RECT workArea = getMonitorWorkArea(settings.monitor);
	
	int width = _base.right - _base.left, height = _base.bottom - _base.top;

	POINT result;
	if (settings.corner == TopLeft || settings.corner == BottomLeft)
		result.x = workArea.left + settings.offset.x;
	else
		result.x = workArea.right - width - settings.offset.x;

	if (settings.corner == TopLeft || settings.corner == TopRight)
		result.y = workArea.top + settings.offset.y;
	else
		result.y = workArea.bottom - height - settings.offset.y;
	
	return result;
}

void APIENTRY notificationHook(HWINEVENTHOOK hWinEventHook, DWORD event, HWND hwnd,
							   LONG idObject, LONG idChild, DWORD idEventThread,
							   DWORD dwmsEventTime)
{
	static const std::wstring trayAlertClass = L"TTrayAlert";
	wchar_t className[MAX_PATH] = {0};
	
	GetClassName(hwnd, className, MAX_PATH);

	if (className != trayAlertClass)
		return;

	RECT rect;
	if (!GetWindowRect(hwnd, &rect))
		return;

	POINT pos = calcWindowPos(rect);
	MoveWindow(hwnd, pos.x, pos.y, rect.right - rect.left, rect.bottom - rect.top, TRUE);
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		settings.iniPath = getWorkingDirectory() + L"/SNU.ini";
		settings.monitor = (unsigned)GetPrivateProfileInt(L"SNU", L"monitor", 0,
														  settings.iniPath.c_str());
		settings.corner = (ScreenCorner)GetPrivateProfileInt(L"SNU", L"corner", 2,
															 settings.iniPath.c_str());
		settings.offset.x = GetPrivateProfileInt(L"SNU", L"offset_x", 0, settings.iniPath.c_str());
		settings.offset.y = GetPrivateProfileInt(L"SNU", L"offset_y", 0, settings.iniPath.c_str());
		break;
	}

	return TRUE;
}