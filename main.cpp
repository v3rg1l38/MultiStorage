#include <Windows.h>
#include <CommCtrl.h>
#include "WindowManager/WindowManager.h"
#include "FrameWindow/FrameWindow.h"
#include "StorageWindow/StorageWindow.h"

#pragma comment(lib, "comctl32.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR czCommand, int nShowWindow)
{
	INITCOMMONCONTROLSEX initCtrls;
	initCtrls.dwICC = ICC_WIN95_CLASSES;
	initCtrls.dwSize = sizeof(INITCOMMONCONTROLSEX);
	InitCommonControlsEx(&initCtrls);
	
	FrameWindow * fWindow = WindowBase<FrameWindow>::getInstance();
	StorageWindow * sWindow = WindowBase<StorageWindow>::getInstance();
	WindowManager::registerClass("Storage",
		hInstance,
		sWindow->WndProc);

	WindowManager::registerClass("MyX",
		hInstance,
		fWindow->WndProc
	);

	HWND mWindow = WindowManager::createWindow("MyX",
		"MyX",
		0,
		0,
		1024,
		768,
		hInstance);

	ShowWindow(mWindow, SW_NORMAL);

	MSG msg;

	while (GetMessage(&msg, NULL, NULL, 0) != 0)
	{
		if (!TranslateMDISysAccel(fWindow->getClientHandle(), &msg))
		{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}
	}

	return static_cast<int>(msg.wParam);


}