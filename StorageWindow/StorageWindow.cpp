#include "StorageWindow.h"

LRESULT StorageWindow::MDICProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		onCreate();
		break;

	//case WM_NOTIFY:
	//{
	//	switch ((reinterpret_cast<LPNMHDR>(lParam))->code)
	//	{
	//	case NM_CLICK:
	//		CList::getDataFromRow(_listHandle, 0, COUNT_COLUMN);
	//	}
	//	break;
	//}
	//break;

	case WM_CLOSE:
	{
		MenuControl mc;
		mc.EnableMenu(_mHwnd, MENU_STORAGE, MENU_STORAGE_LIST);
		DestroyWindow(_mHwnd);
	}
	break;

	case WM_MDIACTIVATE:
	{
		MenuControl mc;
		mc.DisableMenu(_mHwnd, MENU_STORAGE, MENU_STORAGE_LIST);
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
	ListView lV;
	GetClientRect(_mHwnd, &rc);
	_listHandle = lV.createList(_mHwnd, 0, 0, rc.right - rc.left, rc.bottom - rc.top, ID_STORAGE_LIST);
	lV.setTxtBkColor(_listHandle, RGB(179, 248, 255));
	lV.setBkColor(_listHandle, RGB(179, 248, 255));
	lV.insertColumn(_listHandle, COLUMN_CODE, TEXT("Code"), 0x80);
	lV.insertColumn(_listHandle, COLUMN_NAME, TEXT("Name"), 0x120);
	lV.insertColumn(_listHandle, COLUMN_DESCRIPTION, TEXT("Description"), 0x80);
	lV.insertColumn(_listHandle, COLUMN_COUNT, TEXT("Count"), 0x80);
	lV.insertColumn(_listHandle, COLUMN_PACKAGE, TEXT("Package"), 0x80);
	lV.insertColumn(_listHandle, COLUMN_NEEDED, TEXT("Needed"), 0x80);
	lV.insertColumn(_listHandle, COLUMN_RETAILPRICE, TEXT("Retail Price"), 0x80);
	lV.insertColumn(_listHandle, COLUMN_WHOLESALEPRICE, TEXT("Wholesale Price"), 0x80);
	lV.setFullRowSelect(_listHandle);

	for (size_t i = 0; i < 200; ++i)
	{
		lV.insertItem(_listHandle, 9999999);
		lV.setItemInt(_listHandle, i + 1, i, COLUMN_CODE);
		lV.setItemText(_listHandle, TEXT("Visokootporni lanac FI 10"), i, COLUMN_NAME);
		lV.setItemText(_listHandle, TEXT("Lanac FI 10"), i, COLUMN_DESCRIPTION);
		lV.setItemInt(_listHandle, i * 20, i, COLUMN_COUNT);
		lV.setItemInt(_listHandle, i * 10, i, COLUMN_PACKAGE);
		lV.setItemInt(_listHandle, i * 5, i, COLUMN_NEEDED);
		lV.setItemText(_listHandle, TEXT("10.02"), i, COLUMN_RETAILPRICE);
		lV.setItemText(_listHandle, TEXT("8.50"), i, COLUMN_WHOLESALEPRICE);
	}
}


void StorageWindow::onResize(LPARAM lParam)
{
	_cX = LOWORD(lParam);
	_cY = HIWORD(lParam);
	WindowControls::setWindowSize(_listHandle, _cX, _cY);
}
