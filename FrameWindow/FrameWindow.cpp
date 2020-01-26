#include "FrameWindow.h"

void FrameWindow::initilaizeMenu()
{
	HMENU hMenu, hSubMenu;

	hMenu = CreateMenu();

	hSubMenu = CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING | MF_POPUP, reinterpret_cast<UINT>(hSubMenu), Localization::getLocalString(L"MENU_FILE"));
	AppendMenu(hSubMenu, MF_STRING, MENU_FILE_OPEN, Localization::getLocalString(L"MENU_OPEN"));
	AppendMenu(hSubMenu, MF_STRING, MENU_FILE_SAVE, Localization::getLocalString(L"MENU_SAVE"));
	AppendMenu(hSubMenu, MF_STRING, MENU_FILE_LOAD, Localization::getLocalString(L"MENU_LOAD"));
	AppendMenu(hSubMenu, MF_STRING, MENU_FILE_CLOSE, Localization::getLocalString(L"MENU_CLOSE"));

	hSubMenu = CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING | MF_POPUP, reinterpret_cast<UINT>(hSubMenu), Localization::getLocalString(L"MENU_INVOICE"));
	AppendMenu(hSubMenu, MF_STRING, MENU_INVOICE_NEW, Localization::getLocalString(L"MENU_NEW"));
	AppendMenu(hSubMenu, MF_STRING, MENU_INVOICE_LOAD, Localization::getLocalString(L"MENU_LOAD"));
	AppendMenu(hSubMenu, MF_STRING, MENU_INVOICE_LIST, Localization::getLocalString(L"MENU_LIST"));

	hSubMenu = CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING | MF_POPUP, reinterpret_cast<UINT>(hSubMenu), Localization::getLocalString(L"MENU_SETTINGS"));
	AppendMenu(hSubMenu, MF_STRING, MENU_SETTINGS_GLOBAL, Localization::getLocalString(L"MENU_GLOBALSETTINGS"));

	hSubMenu = CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING | MF_POPUP, reinterpret_cast<UINT>(hSubMenu), Localization::getLocalString(L"MENU_STORAGE"));
	AppendMenu(hSubMenu, MF_STRING, MENU_STORAGE_ADD, Localization::getLocalString(L"MENU_STORAGE_ADD"));
	AppendMenu(hSubMenu, MF_STRING, MENU_STORAGE_LIST, Localization::getLocalString(L"MENU_LIST"));
	AppendMenu(hSubMenu, MF_STRING, MENU_STORAGE_EXPORT, Localization::getLocalString(L"MENU_EXPORTSTORAGE"));

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
		TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE /*| TBSTYLE_TRANSPARENT*/,
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

	//DataManagement dm;
	//dm.loadDbSettings();
	//_products = dm.getProductList();
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
		storWind->setProds(&_products);
		storWind->createMDIChild(TEXT("Storage"), TEXT("Storage"), _clientArea);
	}
	break;

	case MENU_INVOICE_NEW:
	{
		InvoiceWindow * invoiceWind = new InvoiceWindow();
		invoiceWind->setProds(&_products);
		invoiceWind->createMDIChild(TEXT("Invoice"), TEXT("Invoice"), _clientArea);
		SetWindowTheme(*invoiceWind, L"DarkMode_Explorer", nullptr);
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
		onCreate();
		break;

	case WM_COMMAND:
		commandHandler(wParam, lParam);
		break;

	case WM_SIZE:
		onChangeSize(lParam);
	break;

	default:
		return DefFrameProc(_mHwnd, _clientArea, msg, wParam, lParam);
	}

	return 0;
}
