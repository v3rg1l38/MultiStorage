#include <Windows.h>
#include <CommCtrl.h>
#include "WindowManager/WindowManager.h"
#include "ListControls/CList.h"

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

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			SetTextColor(hdc, RGB(255, 0, 0));
			SetBkMode(hdc, TRANSPARENT);
			TextOut(hdc, 5, 10, "Hello World", strlen("Hello World"));
			EndPaint(hWnd, &ps);
		}
		break;

		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR czCommand, int nShowWindow)
{
	MSG msg;
	WindowManager::registerClass("MyX", hInstance, WProc);
	HWND myWindow = WindowManager::createWindow("MyX",
		"MyX",
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		600,
		480,
		hInstance);
	UpdateWindow(myWindow);
	ShowWindow(myWindow, 1);

	INITCOMMONCONTROLSEX initCtrls;
	initCtrls.dwICC = ICC_WIN95_CLASSES;
	initCtrls.dwSize = sizeof(INITCOMMONCONTROLSEX);
	InitCommonControlsEx(&initCtrls);

	while (GetMessage(&msg, NULL, NULL, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return static_cast<int>(msg.wParam);

}