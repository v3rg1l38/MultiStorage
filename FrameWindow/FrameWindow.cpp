#include "FrameWindow.h"

LRESULT CALLBACK WProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int cx, cy;

	switch (msg)
	{
	case WM_SIZE:
		cx = LOWORD(lParam);
		cy = HIWORD(lParam);
		
		//WindowControls::setWindowSize(GetDlgItem(hWnd, ID_CLIENTAREA), cx, cy - 30);
		WindowControls::setWindowSize(WindowManager::getWindowHandle("TOOLBAR"), cx, 30);
		SetWindowPos(WindowManager::getWindowHandle("CLIENT"), NULL, 0, 30, cx, cy - 30, SWP_SHOWWINDOW);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case 9800:
			MessageBox(NULL, "Ok", "Info", MB_OK);
			break;

		case MENU_INVOICE_LIST:
			WindowManager::createMDIChild(GetDlgItem(hWnd, ID_CLIENTAREA), "Invoice", "Invoice", 1080, 680);
			break;

		case MENU_STORAGE_LIST:
			WindowManager::createMDIChild(GetDlgItem(hWnd, ID_CLIENTAREA), "Storage", "Storage", 1050, 550);
			break;

		case MENU_FILE_CLOSE:
			PostQuitMessage(0);
			break;

		case SC_MINIMIZE:
		{
			HWND child = reinterpret_cast<HWND>(SendMessage(GetDlgItem(hWnd, ID_CLIENTAREA), WM_MDIGETACTIVE, 0, 0));
			if (child)
				ShowWindow(child, SW_MINIMIZE);
		}
		break;

		case SC_MAXIMIZE:
		{
			HWND child = reinterpret_cast<HWND>(SendMessage(GetDlgItem(hWnd, ID_CLIENTAREA), WM_MDIGETACTIVE, 0, 0));
			if (child)
				ShowWindow(child, SW_MAXIMIZE);
		}
		break;

		case SC_RESTORE:
		{
			HWND child = reinterpret_cast<HWND>(SendMessage(GetDlgItem(hWnd, ID_CLIENTAREA), WM_MDIGETACTIVE, 0, 0));
			if (child)
				ShowWindow(child, SW_NORMAL);
		}
		break;

		case SC_CLOSE:
		{
			HWND child = reinterpret_cast<HWND>(SendMessage(GetDlgItem(hWnd, ID_CLIENTAREA), WM_MDIGETACTIVE, 0, 0));
			if (child)
			{
				SendMessage(child, WM_CLOSE, 0, 0);
				child = reinterpret_cast<HWND>(SendMessage(GetDlgItem(hWnd, ID_CLIENTAREA), WM_MDIGETACTIVE, 0, 0));
				ShowWindow(child, SW_NORMAL);
			}
		}
		break;

		default:
		{
			HWND child = reinterpret_cast<HWND>(SendMessage(GetDlgItem(hWnd, ID_CLIENTAREA), WM_MDIGETACTIVE, 0, 0));
			if (child)
				SendMessage(child, WM_COMMAND, wParam, lParam);
		}
		break;
		}
	}
	break;

	case WM_CREATE:
	{
		CLIENTCREATESTRUCT css;

		HWND clientArea = CreateWindow("MDICLIENT",
			NULL,
			WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE,
			0,
			30,
			0,
			0,
			hWnd,
			(HMENU)ID_CLIENTAREA,
			GetModuleHandle(NULL),
			&css);

		WindowManager::addWindowToList("CLIENT", clientArea);

		HWND hTool = CreateWindowEx(0, 
			TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE, 
			0, 
			0, 
			0, 
			0,
			hWnd, 
			NULL, 
			GetModuleHandle(NULL), 
			NULL);

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

		tbb[2].iBitmap = STD_DELETE;
		tbb[2].fsState = TBSTATE_ENABLED;
		tbb[2].fsStyle = TBSTYLE_BUTTON;
		tbb[2].idCommand = 9802;

		SendMessage(hTool, TB_AUTOSIZE, 0, 0);
		SendMessage(hTool, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)&tbb);

		WindowManager::addWindowToList("TOOLBAR", hTool);
	}
	break;

	default:
		return DefFrameProc(hWnd, GetDlgItem(hWnd, ID_CLIENTAREA), msg, wParam, lParam);
	}

	return 0;
}