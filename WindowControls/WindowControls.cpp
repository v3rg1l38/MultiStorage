#include "WindowControls.h"

void WindowControls::setWindowSize(const HWND hWnd, const int & cX, const int & cY)
{
	SetWindowPos(hWnd, NULL, 0, 0, cX, cY, SWP_NOREPOSITION);
}

void WindowControls::initializeMenu(const HWND winHandle)
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

	SetMenu(winHandle, hMenu);
}
