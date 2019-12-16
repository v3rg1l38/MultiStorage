#include "FrameWindow.h"
#include "../StorageWindow/StorageWindow.h"

LRESULT FrameWindow::MessageHandler(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SIZE:
		_cX = LOWORD(lParam);
		_cY = HIWORD(lParam);

		WindowControls::setWindowSize(_toolBar, _cX, 30);
		SetWindowPos(_clientHwnd, NULL, 0, 30, _cX, _cY - 30, SWP_SHOWWINDOW);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case 9800:
		{
			MessageBox(NULL, "bok", "Info", MB_OK);
		}
		break;

		case MENU_INVOICE_LIST:
			//WindowManager::createMDIChild(GetDlgItem(hWnd, ID_CLIENTAREA), "Invoice", "Invoice", 1080, 680);
			CreateWindowEx(WS_EX_MDICHILD, "Invoice",
				"Invoice",
				WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE,
				0,
				0,
				640,
				580,
				_clientHwnd,
				NULL,
				GetModuleHandle(NULL),
				NULL);


			break;

		case MENU_STORAGE_LIST:
			WindowManager::createMDIChild(_clientHwnd, "Storage", "Storage", 1050, 550);
			break;

		case MENU_FILE_CLOSE:
			PostQuitMessage(0);
			break;

		case SC_MINIMIZE:
		{
			HWND child = reinterpret_cast<HWND>(SendMessage(_clientHwnd, WM_MDIGETACTIVE, 0, 0));
			if (child)
				ShowWindow(child, SW_MINIMIZE);
		}
		break;

		case SC_MAXIMIZE:
		{
			HWND child = reinterpret_cast<HWND>(SendMessage(_clientHwnd, WM_MDIGETACTIVE, 0, 0));
			if (child)
				ShowWindow(child, SW_MAXIMIZE);
		}
		break;

		case SC_RESTORE:
		{
			HWND child = reinterpret_cast<HWND>(SendMessage(_clientHwnd, WM_MDIGETACTIVE, 0, 0));
			if (child)
				ShowWindow(child, SW_NORMAL);
		}
		break;

		case SC_CLOSE:
		{
			HWND child = reinterpret_cast<HWND>(SendMessage(_clientHwnd, WM_MDIGETACTIVE, 0, 0));
			if (child)
			{
				SendMessage(child, WM_CLOSE, 0, 0);
				child = reinterpret_cast<HWND>(SendMessage(_clientHwnd, WM_MDIGETACTIVE, 0, 0));
				ShowWindow(child, SW_NORMAL);
			}
		}
		break;

		default:
		{
			HWND child = reinterpret_cast<HWND>(SendMessage(_clientHwnd, WM_MDIGETACTIVE, 0, 0));
			if (child)
				SendMessage(child, WM_COMMAND, wParam, lParam);
		}
		break;
		}
	}
	break;

	case WM_CREATE:
	{
		initilaizeMenu();
		setClientAreaBackground();

		CLIENTCREATESTRUCT css;
		_clientHwnd = CreateWindow("MDICLIENT",
			NULL,
			WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE,
			0,
			30,
			0,
			0,
			_hWnd,
			(HMENU)ID_CLIENTAREA,
			GetModuleHandle(NULL),
			&css);

		WindowManager::addWindowToList("CLIENT", _clientHwnd);

		_toolBar = CreateWindowEx(0,
			TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE,
			0,
			0,
			0,
			0,
			_hWnd,
			NULL,
			GetModuleHandle(NULL),
			NULL);

		SendMessage(_toolBar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);

		TBBUTTON tbb[3];
		TBADDBITMAP tbab;
		tbab.hInst = HINST_COMMCTRL;
		tbab.nID = IDB_STD_SMALL_COLOR;
		SendMessage(_toolBar, TB_ADDBITMAP, 0, (LPARAM)&tbab);
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

		SendMessage(_toolBar, TB_AUTOSIZE, 0, 0);
		SendMessage(_toolBar, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)&tbb);

		WindowManager::addWindowToList("TOOLBAR", _toolBar);
	}
	break;

	default:
		return DefFrameProc(_hWnd, _clientHwnd, msg, wParam, lParam);
	}

	return 0;
}

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

	SetMenu(_hWnd, hMenu);
}

bool FrameWindow::setClientAreaBackground()
{
	WNDCLASS wcc = {};
	GetClassInfo(GetModuleHandle(NULL), "MDICLIENT", &wcc);
	HBRUSH brush = CreateSolidBrush(RGB(22, 108, 145));
	wcc.hbrBackground = brush;

	return RegisterClass(&wcc) ? true : false;
}
