#include "FrameWindow.h"
#include "../StorageWindow/StorageWindow.h"
#include "../InvoiceWindow/InvoiceWindow.h"

void FrameWindow::initilaizeMenu()
{
	HMENU hMenu, hSubMenu;

	hMenu = CreateMenu();

	hSubMenu = CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING | MF_POPUP, reinterpret_cast<UINT>(hSubMenu), TEXT("&File"));
	AppendMenu(hSubMenu, MF_STRING, MENU_FILE_OPEN, TEXT("&Open"));
	AppendMenu(hSubMenu, MF_STRING, MENU_FILE_SAVE, TEXT("&Save"));
	AppendMenu(hSubMenu, MF_STRING, MENU_FILE_LOAD, TEXT("&Load"));
	AppendMenu(hSubMenu, MF_STRING, MENU_FILE_CLOSE, TEXT("&Close"));

	hSubMenu = CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING | MF_POPUP, reinterpret_cast<UINT>(hSubMenu), TEXT("&Invoice"));
	AppendMenu(hSubMenu, MF_STRING, MENU_INVOICE_NEW, TEXT("&New"));
	AppendMenu(hSubMenu, MF_STRING, MENU_INVOICE_LOAD, TEXT("&Load"));
	AppendMenu(hSubMenu, MF_STRING, MENU_INVOICE_LIST, TEXT("L&ist"));

	hSubMenu = CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING | MF_POPUP, reinterpret_cast<UINT>(hSubMenu), TEXT("&Settings"));
	AppendMenu(hSubMenu, MF_STRING, MENU_SETTINGS_GLOBAL, TEXT("&Global Settings"));

	hSubMenu = CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING | MF_POPUP, reinterpret_cast<UINT>(hSubMenu), TEXT("S&torage"));
	AppendMenu(hSubMenu, MF_STRING, MENU_STORAGE_LIST, TEXT("&List"));
	AppendMenu(hSubMenu, MF_STRING, MENU_STORAGE_EXPORT, TEXT("&Export Storage"));

	SetMenu(_mHwnd, hMenu);
}

void FrameWindow::setClientAreaBackground()
{
	HBRUSH brush = CreateSolidBrush(RGB(22, 108, 145));
	SetClassLongPtr(_clientArea, GCL_HBRBACKGROUND, reinterpret_cast<LONG_PTR>(brush));
}

void FrameWindow::onCreate()
{
	initilaizeMenu();

	CLIENTCREATESTRUCT css;
	_clientArea = CreateWindow(TEXT("MDICLIENT"),
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

	setClientAreaBackground();

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

	_database.Host("192.168.1.96").Port("3306").Username("vergil").Password("matija").DbName("MultiStorage")
		.SqlCommand("SELECT * FROM Products");
	_database.fetchData();
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

	case MENU_FILE_CLOSE:
		DestroyWindow(_clientArea);
		PostQuitMessage(0);
		break;

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
			ShowWindow(child, SW_NORMAL);
			SendMessage(child, WM_CLOSE, 0, 0);
			child = reinterpret_cast<HWND>(SendMessage(_clientArea, WM_MDIGETACTIVE, 0, 0));
		}
	}
	break;

	case MENU_STORAGE_LIST:
	{
		StorageWindow *storWind = new StorageWindow();
		storWind->setProds(&_database.getProductList());
		storWind->createMDIChild(TEXT("Storage"), TEXT("Storage"), _clientArea);
	}
	break;

	case MENU_INVOICE_LIST:
	{
		InvoiceWindow * invoiceWind = new InvoiceWindow();
		invoiceWind->setProds(&_database.getProductList());
		invoiceWind->createMDIChild(TEXT("Invoice"), 
			TEXT("Invoice"), 
			_clientArea,
			WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CHILD,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			854,
			420);
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
		onCreate();
	}
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
