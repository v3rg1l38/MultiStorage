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
	AppendMenu(hSubMenu, MF_STRING, 9000, "&Open");
	AppendMenu(hSubMenu, MF_STRING, 9001, "&Save");
	AppendMenu(hSubMenu, MF_STRING, 9002, "&Load");

	SetMenu(winHandle, hMenu);
}
