#include <Windows.h>
#include <CommCtrl.h>
#include "WindowManager/WindowManager.h"
#include "WindowControls/WindowControls.h"
#include "FrameWindow/FrameWindow.h"
#include "InvoiceWindow/InvoiceWindow.h"
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

	WNDCLASS wcc = {};
	GetClassInfo(hInstance, "MDICLIENT", &wcc);
	HBRUSH brush = CreateSolidBrush(RGB(22, 108, 145));
	wcc.hbrBackground = brush;

	if (!RegisterClass(&wcc))
	{
		MessageBox(NULL, "Unable to register new class", "Error", MB_OK);
		return 0;
	}

	MSG msg;
	WindowManager::registerClass("MyX", hInstance, WProc);
	WindowManager::registerClass("Invoice", hInstance, InvoiceProc);
	WindowManager::registerClass("Storage", hInstance, Storage::StorageProc);

	//HWND frameWindow = WindowManager::createWindow("MyX",
	//	"MyX",
	//	CW_USEDEFAULT,
	//	CW_USEDEFAULT,
	//	640,
	//	480,
	//	hInstance
	//	);
	Storage st;

	HWND frameWindow = CreateWindow("MyX",
		"MyX",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		640,
		480,
		NULL,
		NULL,
		hInstance,
		&st);

	WindowControls wc;
	wc.initializeMenu(frameWindow);
	UpdateWindow(frameWindow);
	ShowWindow(frameWindow, SW_MAXIMIZE);

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