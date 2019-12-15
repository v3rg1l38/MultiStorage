#include <Windows.h>
#include <CommCtrl.h>
#include "WindowManager/WindowManager.h"
#include "ListControls/CList.h"
#include "WindowControls/WindowControls.h"
#include "Invoice/Invoice.h"

#pragma comment(lib, "comctl32.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

HWND clientArea;

LRESULT CALLBACK ChProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND edit;

	switch (msg)
	{
	case WM_CREATE:
	{
		edit = WindowManager::createWindow("",
			"EDIT",
			5,
			30,
			120,
			30,
			GetModuleHandle(NULL),
			hWnd,
			ES_AUTOHSCROLL | WS_CHILD | WS_VISIBLE);

		WindowManager::createWindow("Push me",
			"BUTTON",
			140,
			30,
			80,
			30,
			GetModuleHandle(NULL),
			hWnd,
			BS_DEFPUSHBUTTON | WS_CHILD | WS_VISIBLE,
			reinterpret_cast<HMENU>(9800));

		WindowControls::setEditText(edit, "Ja sam mali pero");
		SendMessage(edit, EM_SETSEL, 1, 6);
	}
	break;

	case WM_SETFOCUS:
		SetFocus(edit);
		break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case 9800:
		{
			WindowControls::replaceSelectedText(edit, "Ajajajajaja");
		}
		break;
		}
		break;
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
	static int cX, cY;
	static HWND list;

	switch (msg)
	{
	case WM_CREATE:
	{
		RECT rc;
		GetClientRect(hWnd, &rc);
		list = CList::createList(hWnd,
			0,
			0,
			rc.right - 160,
			rc.bottom - 150,
			NULL);
		CList::setFullRowSelect(list);
		CList::insertColumn(list,
			0,
			"Year",
			0x54);
		CList::insertColumn(list,
			1,
			"Name",
			0x124);
		CList::insertItem(list, 9999);
		CList::insertItem(list, 9999);
		CList::setItemText(list, "2018", 0, 0);
		CList::setItemText(list, "Storage", 0, 1);		
		CList::setItemText(list, "2019", 1, 0);
		CList::setItemText(list, "Storage", 1, 1);
	}
	break;

	case WM_SIZE:
	{
		cX = LOWORD(lParam);
		cY = HIWORD(lParam);
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
			case MENU_INVOICE_LIST:
				WindowManager::createMDIChild(clientArea, "Proba 123", "Testing", 1080, 680);
				break;

			case MENU_FILE_SAVE:
				WindowManager::createMDIChild(clientArea, "Proba 1223", "Proba", 950, 550);
				break;

			case MENU_FILE_CLOSE:
				PostQuitMessage(0);
				break;

			case SC_MINIMIZE:
			{
				HWND child = reinterpret_cast<HWND>(SendMessage(clientArea, WM_MDIGETACTIVE, 0, 0));
				if (child)
					ShowWindow(child, SW_MINIMIZE);
			}
			break;

			case SC_MAXIMIZE:
			{
				HWND child = reinterpret_cast<HWND>(SendMessage(clientArea, WM_MDIGETACTIVE, 0, 0));
				if (child)
					ShowWindow(child, SW_MAXIMIZE);
			}
			break;

			case SC_RESTORE:
			{
				HWND child = reinterpret_cast<HWND>(SendMessage(clientArea, WM_MDIGETACTIVE, 0, 0));
				if (child)
					ShowWindow(child, SW_NORMAL);
			}
			break;

			case SC_CLOSE:
			{
				HWND child = reinterpret_cast<HWND>(SendMessage(clientArea, WM_MDIGETACTIVE, 0, 0));
				if (child)
				{
					SendMessage(child, WM_CLOSE, 0, 0);
					child = reinterpret_cast<HWND>(SendMessage(clientArea, WM_MDIGETACTIVE, 0, 0));
					ShowWindow(child, SW_NORMAL);
				}
			}
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