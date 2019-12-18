#include "FrameWindow.h"
#include <memory>
#include "../StorageWindow/StorageWindow.h"
#include "../InvoiceWindow/InvoiceWindow.h"

void FrameWindow::initilaizeMenu()
{
	HMENU hMenu, hSubMenu;

	hMenu = CreateMenu();

	hSubMenu = CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING | MF_POPUP, reinterpret_cast<UINT>(hSubMenu), "&File");
	AppendMenu(hSubMenu, MF_STRING, MENU_FILE_OPEN, "&Open");
	AppendMenu(hSubMenu, MF_STRING, MENU_FILE_SAVE, "&Save");
	AppendMenu(hSubMenu, MF_STRING, MENU_FILE_LOAD, "&Load");
	AppendMenu(hSubMenu, MF_STRING, MENU_FILE_CLOSE, "&Close");

	hSubMenu = CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING | MF_POPUP, reinterpret_cast<UINT>(hSubMenu), "&Invoice");
	AppendMenu(hSubMenu, MF_STRING, MENU_INVOICE_NEW, "&New");
	AppendMenu(hSubMenu, MF_STRING, MENU_INVOICE_LOAD, "&Load");
	AppendMenu(hSubMenu, MF_STRING, MENU_INVOICE_LIST, "L&ist");

	hSubMenu = CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING | MF_POPUP, reinterpret_cast<UINT>(hSubMenu), "&Settings");
	AppendMenu(hSubMenu, MF_STRING, MENU_SETTINGS_GLOBAL, "&Global Settings");

	hSubMenu = CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING | MF_POPUP, reinterpret_cast<UINT>(hSubMenu), "S&torage");
	AppendMenu(hSubMenu, MF_STRING, MENU_STORAGE_LIST, "&List");
	AppendMenu(hSubMenu, MF_STRING, MENU_STORAGE_EXPORT, "&Export Storage");

	SetMenu(_mHwnd, hMenu);
}

bool FrameWindow::setClientAreaBackground()
{
	WNDCLASS wcc = {};
	GetClassInfo(GetModuleHandle(NULL), "MDICLIENT", &wcc);
	HBRUSH brush = CreateSolidBrush(RGB(22, 108, 145));
	wcc.hbrBackground = brush;

	return RegisterClass(&wcc) ? true : false;
}

void FrameWindow::onCreate()
{
	initilaizeMenu();
	setClientAreaBackground();

	CLIENTCREATESTRUCT css;
	_clientArea = CreateWindow("MDICLIENT",
		NULL,
		WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE,
		0,
		30,
		0,
		0,
		_mHwnd,
		(HMENU)ID_CLIENTAREA,
		GetModuleHandle(NULL),
		&css);

	_toolbar = CreateWindowEx(0,
		TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE,
		0,
		0,
		0,
		0,
		_mHwnd,
		NULL,
		GetModuleHandle(NULL),
		NULL);

	SendMessage(_toolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);

	TBBUTTON tbb[3];
	TBADDBITMAP tbab;
	tbab.hInst = HINST_COMMCTRL;
	tbab.nID = IDB_STD_SMALL_COLOR;
	SendMessage(_toolbar, TB_ADDBITMAP, 0, (LPARAM)&tbab);
	ZeroMemory(tbb, sizeof(tbb));
	tbb[0].iBitmap = STD_FILENEW;
	tbb[0].fsState = TBSTATE_ENABLED;
	tbb[0].fsStyle = TBSTYLE_BUTTON;
	tbb[0].idCommand = 9800;

	tbb[1].iBitmap = STD_FILEOPEN;
	tbb[1].fsState = TBSTATE_ENABLED;
	tbb[1].fsStyle = TBSTYLE_BUTTON;
	tbb[1].idCommand = 9801;

	tbb[2].iBitmap = STD_DELETE;
	tbb[2].fsState = TBSTATE_ENABLED;
	tbb[2].fsStyle = TBSTYLE_BUTTON;
	tbb[2].idCommand = 9802;

	SendMessage(_toolbar, TB_AUTOSIZE, 0, 0);
	SendMessage(_toolbar, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)&tbb);
}

void FrameWindow::onChangeSize(LPARAM lParam)
{
	_cX = LOWORD(lParam);
	_cY = HIWORD(lParam);
	
	WindowControls::setWindowSize(_toolbar, _cX, 30);
	SetWindowPos(_clientArea, NULL, 0, 30, _cX, _cY - 30, SWP_SHOWWINDOW);
}

void FrameWindow::commandHandler(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case SC_MINIMIZE:
	{
		HWND child = reinterpret_cast<HWND>(SendMessage(_clientArea, WM_MDIGETACTIVE, 0, 0));
		if (child)
			ShowWindow(child, SW_MINIMIZE);
	}
	break;

	case SC_MAXIMIZE:
	{
		HWND child = reinterpret_cast<HWND>(SendMessage(_clientArea, WM_MDIGETACTIVE, 0, 0));
		if (child)
			ShowWindow(child, SW_MAXIMIZE);
	}
	break;

	case SC_RESTORE:
	{
		HWND child = reinterpret_cast<HWND>(SendMessage(_clientArea, WM_MDIGETACTIVE, 0, 0));
		if (child)
			ShowWindow(child, SW_NORMAL);
	}
	break;

	case SC_CLOSE:
	{
		HWND child = reinterpret_cast<HWND>(SendMessage(_clientArea, WM_MDIGETACTIVE, 0, 0));
		if (child)
		{
			SendMessage(child, WM_CLOSE, 0, 0);
			child = reinterpret_cast<HWND>(SendMessage(_clientArea, WM_MDIGETACTIVE, 0, 0));
			ShowWindow(child, SW_NORMAL);
		}
	}
	break;

	case MENU_STORAGE_LIST:
	{
		StorageWindow *storWind = new StorageWindow();
		storWind->createMDIChild("Storage", "Storage", _clientArea);
	}
	break;

	case MENU_INVOICE_LIST:
	{
		InvoiceWindow * invoiceWind = new InvoiceWindow();
		invoiceWind->createMDIChild("Invoice", "Invoice", _clientArea);
	}
	break;

	default:
	{
		HWND child = reinterpret_cast<HWND>(SendMessage(_clientArea, WM_MDIGETACTIVE, 0, 0));
		if (child)
			SendMessage(child, WM_COMMAND, wParam, lParam);
	}
	break;
	}
}

LRESULT FrameWindow::FrameWndProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		this->onCreate();
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_COMMAND:
	{
		commandHandler(wParam, lParam);
	}
	break;

	case WM_SIZE:
		onChangeSize(lParam);
	break;

	default:
		return DefFrameProc(_mHwnd, _clientArea, msg, wParam, lParam);
	}

	return 0;
}
