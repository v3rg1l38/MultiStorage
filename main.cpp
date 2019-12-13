#include <Windows.h>
#include <CommCtrl.h>
#include "WindowManager/WindowManager.h"
#include "ListControls/CList.h"
#include "WindowControls/WindowControls.h"

#pragma comment(lib, "comctl32.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

HWND clientArea = NULL;

LRESULT CALLBACK ChProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 10, 20, "Proba", strlen("Proba"));
		EndPaint(hWnd, &ps);
	}
	break;

	default:
		return DefMDIChildProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

LRESULT CALLBACK ChildProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		HWND list = CList::createList(hWnd,
			0,
			0,
			400,
			400,
			NULL);
		CList::setFullRowSelect(list);

		CList::insertColumn(list,
			0,
			"Code",
			0x54);
		CList::insertColumn(list,
			1,
			"Name",
			0x124);
		CList::insertItem(list, 9999);
		CList::setItemText(list, "12000", 0, 0);
		CList::setItemText(list, "Visokootporni lanac FI 10", 0, 1);
	}
	break;

	case WM_DESTROY:
		MessageBox(NULL, "Bye", "Info", MB_OK);
		break;

	//case WM_MDIACTIVATE:
	//	SetFocus(hEdit);
	//	break;

	//case WM_SETFOCUS:
	//	SetFocus(hEdit);
	//	return DefMDIChildProc(hWnd, msg, wParam, lParam);

	default:
		return DefMDIChildProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

LRESULT CALLBACK WProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int cx, cy;

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
			WindowManager::createMDIChild(clientArea, "Proba 1223", "Proba", rc.right, rc.bottom);

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
			return DefFrameProc(hWnd, clientArea, msg, wParam, lParam);
	}

	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR czCommand, int nShowWindow)
{
	MSG msg;
	WindowManager::registerClass("MyX", hInstance, WProc);
	WindowManager::registerClass("Testing", hInstance, ChildProc);
	WindowManager::registerClass("Proba", hInstance, ChProc);
	HWND myWindow = WindowManager::createWindow("MyX",
		"MyX",
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		640,
		480,
		hInstance
		);
	WindowControls wc;
	wc.initializeMenu(myWindow);
	UpdateWindow(myWindow);
	ShowWindow(myWindow, SW_MAXIMIZE);

	INITCOMMONCONTROLSEX initCtrls;
	initCtrls.dwICC = ICC_WIN95_CLASSES;
	initCtrls.dwSize = sizeof(INITCOMMONCONTROLSEX);
	InitCommonControlsEx(&initCtrls);

	while (GetMessage(&msg, NULL, NULL, 0))
	{
		if (!TranslateMDISysAccel(clientArea, &msg))
		{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}
	}
	
	return static_cast<int>(msg.wParam);

}