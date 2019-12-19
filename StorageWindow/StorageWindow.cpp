#include "StorageWindow.h"

LRESULT StorageWindow::MDICProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		onCreate();
		break;

	case WM_CLOSE:
	{
		unsigned int FLAG = MF_ENABLED;
		HMENU hMenu, hSubMenu;
		HWND parent = GetParent(GetParent(_mHwnd));
		hMenu = GetMenu(parent);

		hSubMenu = GetSubMenu(hMenu, MENU_STORAGE);
		EnableMenuItem(hSubMenu, MENU_STORAGE_LIST, MF_BYCOMMAND | FLAG);
		DrawMenuBar(parent);
		DestroyWindow(_mHwnd);
	}
	break;

	case WM_MDIACTIVATE:
	{
		unsigned int FLAG = MF_GRAYED;
		HMENU hMenu, hSubMenu;
		HWND parent = GetParent(GetParent(_mHwnd));
		hMenu = GetMenu(parent);
	
		hSubMenu = GetSubMenu(hMenu, MENU_STORAGE);
		EnableMenuItem(hSubMenu, MENU_STORAGE_LIST, MF_BYCOMMAND | FLAG);
		DrawMenuBar(parent);
	}
	break;

	case WM_SIZE:
		onResize(lParam);
		return DefMDIChildProc(_mHwnd, msg, wParam, lParam);

	default:
		return DefMDIChildProc(_mHwnd, msg, wParam, lParam);
	}

	return 0;
}

void StorageWindow::onCreate()
{
	RECT rc;
	GetClientRect(_mHwnd, &rc);
	_listHandle = CList::createList(_mHwnd, 0, 0, rc.right - rc.left, rc.bottom - rc.top, ID_STORAGE_LIST);
	CList::setTxtBkColor(_listHandle, RGB(179, 248, 255));
	CList::setBkColor(_listHandle, RGB(179, 248, 255));
	CList::insertColumn(_listHandle, CODE_COLUMN, TEXT("Code"), 0x80);
	CList::insertColumn(_listHandle, NAME_COLUMN, TEXT("Name"), 0x120);
	CList::insertColumn(_listHandle, DESCR_COLUMN, TEXT("Description"), 0x80);
	CList::insertColumn(_listHandle, COUNT_COLUMN, TEXT("Count"), 0x80);
	CList::insertColumn(_listHandle, PACKAGE_COLUMN, TEXT("Package"), 0x80);
	CList::insertColumn(_listHandle, NEEDED_COLUMN, TEXT("Needed"), 0x80);
	CList::insertColumn(_listHandle, RETAILPRICE_COLUMN, TEXT("Retail Price"), 0x80);
	CList::insertColumn(_listHandle, WHOLESALE_COLUMN, TEXT("Wholesale Price"), 0x80);
	CList::setFullRowSelect(_listHandle);

	for (size_t i = 0; i < 200; ++i)
	{
		CList::insertItem(_listHandle, 9999999);
		CList::setItemInt(_listHandle, i + 1, i, CODE_COLUMN);
		CList::setItemText(_listHandle, TEXT("Visokootporni lanac FI 10"), i, NAME_COLUMN);
		CList::setItemText(_listHandle, TEXT("Lanac FI 10"), i, DESCR_COLUMN);
		CList::setItemInt(_listHandle, i * 20, i, COUNT_COLUMN);
		CList::setItemInt(_listHandle, i * 10, i, PACKAGE_COLUMN);
		CList::setItemInt(_listHandle, i * 5, i, NEEDED_COLUMN);
		CList::setItemText(_listHandle, TEXT("10.02"), i, RETAILPRICE_COLUMN);
		CList::setItemText(_listHandle, TEXT("8.50"), i, WHOLESALE_COLUMN);
	}
}


void StorageWindow::onResize(LPARAM lParam)
{
	_cX = LOWORD(lParam);
	_cY = HIWORD(lParam);
	WindowControls::setWindowSize(_listHandle, _cX, _cY);
}
