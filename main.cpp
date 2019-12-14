#include <Windows.h>
#include <CommCtrl.h>
#include "WindowManager/WindowManager.h"
#include "ListControls/CList.h"
#include "WindowControls/WindowControls.h"

#pragma comment(lib, "comctl32.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

HWND clientArea;

LRESULT CALLBACK ChProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case SC_MINIMIZE:
			ShowWindow(hWnd, SW_MINIMIZE);
			break;

		case SC_RESTORE:
			ShowWindow(hWnd, SW_NORMAL);
			break;

		case SC_CLOSE:
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 10, 20, "Proba", strlen("Proba"));
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_SIZE:
		return DefMDIChildProc(hWnd, msg, wParam, lParam);

	default:
		return DefMDIChildProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

LRESULT CALLBACK ChildProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case SC_MINIMIZE:
			ShowWindow(hWnd, SW_MINIMIZE);
			break;

		case SC_RESTORE:
			ShowWindow(hWnd, SW_NORMAL);
			break;

		case SC_CLOSE:
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		}
	}
	break;

	case WM_SIZE:
		return DefMDIChildProc(hWnd, msg, wParam, lParam);

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
		return DefWindowProc(hWnd, msg, wParam, lParam);

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case 9000:
				WindowManager::createMDIChild(clientArea, "Proba 123", "Testing", 480, 250);
				break;

			case 9001:
				WindowManager::createMDIChild(clientArea, "Proba 1223", "Proba", 450, 250);
				break;

			default:
			{
				HWND child = reinterpret_cast<HWND>(SendMessage(clientArea, WM_MDIGETACTIVE, 0, 0));
				if (child)
					SendMessage(child, WM_COMMAND, wParam, lParam);
			}
			break;
			}
		}
		break;

		case WM_CREATE:
		{
			RECT rc;
			GetClientRect(hWnd, &rc);
			CLIENTCREATESTRUCT css;

			clientArea = CreateWindow("MDICLIENT",
				NULL, 
				WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE,
				0,
				30,
				rc.right - rc.left,
				rc.bottom - rc.top,
				hWnd,
				NULL,
				GetModuleHandle(NULL),
				&css);

			/*HWND hTool = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0,
				hWnd, NULL, GetModuleHandle(NULL), NULL);
			SendMessage(hTool, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
			TBBUTTON tbb[3];
			TBADDBITMAP tbab;
			tbab.hInst = HINST_COMMCTRL;
			tbab.nID = IDB_STD_SMALL_COLOR;
			SendMessage(hTool, TB_ADDBITMAP, 0, (LPARAM)&tbab);
			ZeroMemory(tbb, sizeof(tbb));
			tbb[0].iBitmap = STD_FILENEW;
			tbb[0].fsState = TBSTATE_ENABLED;
			tbb[0].fsStyle = TBSTYLE_BUTTON;
			tbb[0].idCommand = 9800;

			tbb[1].iBitmap = STD_FILEOPEN;
			tbb[1].fsState = TBSTATE_ENABLED;
			tbb[1].fsStyle = TBSTYLE_BUTTON;
			tbb[1].idCommand = 9801;

			tbb[2].iBitmap = STD_FILESAVE;
			tbb[2].fsState = TBSTATE_ENABLED;
			tbb[2].fsStyle = TBSTYLE_BUTTON;
			tbb[2].idCommand = 9802;

			SendMessage(hTool, TB_AUTOSIZE, 0, 0);
			SendMessage(hTool, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)&tbb);*/
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
	INITCOMMONCONTROLSEX initCtrls;
	initCtrls.dwICC = ICC_WIN95_CLASSES;
	initCtrls.dwSize = sizeof(INITCOMMONCONTROLSEX);
	InitCommonControlsEx(&initCtrls);

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

	while (GetMessage(&msg, NULL, NULL, 0) != 0)
	{
		if (!TranslateMDISysAccel(clientArea, &msg))
		{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}
	}
	
	return static_cast<int>(msg.wParam);

}