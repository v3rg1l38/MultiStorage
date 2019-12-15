#include "StorageWindow.h"

LRESULT CALLBACK StorageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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