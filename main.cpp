#include <Windows.h>
#include <CommCtrl.h>
#include "WindowManager/WindowManager.h"
#include "ListControls/CList.h"
#include "WindowControls/WindowControls.h"

#pragma comment(lib, "comctl32.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

LRESULT CALLBACK ChildProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		HFONT hfDefault;
		HWND hEdit;

		// Create Edit Control

		hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "",
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
			0, 0, 100, 100, hWnd, NULL, GetModuleHandle(NULL), NULL);
		if (hEdit == NULL)
			MessageBox(hWnd, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);

		hfDefault = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		SendMessage(hEdit, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
	}
	break;
	case WM_SIZE:
	{
		RECT rcClient;

		// Calculate remaining height and size edit

		GetClientRect(hWnd, &rcClient);
	}
	return DefMDIChildProc(hWnd, msg, wParam, lParam);

	default:
		return DefMDIChildProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

LRESULT CALLBACK WProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int cx, cy;
	static HWND clientArea;

	switch (msg)
	{
	case WM_SIZE:
		cx = LOWORD(lParam);
		cy = HIWORD(lParam);
		WindowControls::setWindowSize(clientArea, cx, cy);
		break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_CREATE:
		{
			RECT rc;
			GetClientRect(hWnd, &rc);
			CLIENTCREATESTRUCT css;
		
			clientArea = CreateWindow("MDICLIENT",
				NULL, WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE,
				0,
				0,
				rc.right - rc.left,
				rc.bottom - rc.top,
				hWnd,
				NULL,
				GetModuleHandle(NULL),
				&css);

			WindowManager::createMDIChild(clientArea, "Proba 123", "Testing", rc.right, rc.bottom);

		}
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
	WindowManager::registerClass("Testing", hInstance, ChildProc);
	HWND myWindow = WindowManager::createWindow("MyX",
		"MyX",
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		640,
		480,
		hInstance
		);
	UpdateWindow(myWindow);
	ShowWindow(myWindow, SW_MAXIMIZE);

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