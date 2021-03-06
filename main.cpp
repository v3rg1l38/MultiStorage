#define UNICODE

#include <Windows.h>
#include <Uxtheme.h>
#include "FrameWindow/FrameWindow.h"
#include "AppData/AppData.h"
#include "Localization/Localization.h"
#include <dwmapi.h>

#pragma comment(lib, "Dwmapi.lib")
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "UxTheme.lib")
#pragma comment(lib, "User32.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR czCommand, int nShowWindow)
{
	if (!AppData::loadAppParams(AppData::g_AppParams) || 
		!Localization::loadLanguage(AppData::g_AppParams.getProp(AppData::APP_PROPS::AP_LANG)))
	{
		return 0;
	}

	FrameWindow * frameWindow = new FrameWindow();
	frameWindow->createWindow(TEXT("MVX Store"));
	SetWindowTheme(*frameWindow, L"DarkMode_Explorer", nullptr);
	const BOOL isD = true;
	HRESULT p = DwmSetWindowAttribute(*frameWindow, 19, &isD, sizeof(isD));
	ShowWindow(*frameWindow, SW_MAXIMIZE);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if (!TranslateMDISysAccel(frameWindow->getClientArea(), &msg))
		{
			if (!IsDialogMessage(GetWindow(frameWindow->getClientArea(), GW_CHILD), &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

	return static_cast<int>(msg.wParam);
}