#include <Windows.h>
#include <CommCtrl.h>
#include "WindowManager/WindowManager.h"
#include "FrameWindow/FrameWindow.h"

#pragma comment(lib, "comctl32.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

LRESULT CALLBACK WProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR czCommand, int nShowWindow)
{
	INITCOMMONCONTROLSEX initCtrls;
	initCtrls.dwICC = ICC_WIN95_CLASSES;
	initCtrls.dwSize = sizeof(INITCOMMONCONTROLSEX);
	InitCommonControlsEx(&initCtrls);
	
	FrameWindow * fWindow = WindowBase<FrameWindow>::getInstance();

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
		if (!TranslateMDISysAccel(WindowManager::getWindowHandle("CLIENT"), &msg))
		{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}
	}

	return static_cast<int>(msg.wParam);


}