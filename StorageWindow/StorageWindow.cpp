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
	GetClientRect(_mHwnd, &rc);
	_listView.createList(_mHwnd, 0, 0, rc.right - rc.left, rc.bottom - rc.top, ID_STORAGE_LIST);
	_listView.setTxtBkColor(RGB(179, 248, 255));
	_listView.setBkColor( RGB(179, 248, 255));
	_listView.insertColumn(COLUMN_CODE, TEXT("Code"), 0x80);
	_listView.insertColumn(COLUMN_NAME, TEXT("Name"), 0x120);
	_listView.insertColumn(COLUMN_DESCRIPTION, TEXT("Description"), 0x80);
	_listView.insertColumn(COLUMN_COUNT, TEXT("Count"), 0x80);
	_listView.insertColumn(COLUMN_PACKAGE, TEXT("Package"), 0x80);
	_listView.insertColumn(COLUMN_NEEDED, TEXT("Needed"), 0x80);
	_listView.insertColumn(COLUMN_RETAILPRICE, TEXT("Retail Price"), 0x80);
	_listView.insertColumn(COLUMN_WHOLESALEPRICE, TEXT("Wholesale Price"), 0x80);
	_listView.setFullRowSelect();

	for (size_t i = 0; i < 200; ++i)
	{
		_listView.insertItem(9999999);
		_listView.setItemInt(i + 1, i, COLUMN_CODE);
		_listView.setItemText(TEXT("Visokootporni lanac FI 10"), i, COLUMN_NAME);
		_listView.setItemText(TEXT("Lanac FI 10"), i, COLUMN_DESCRIPTION);
		_listView.setItemInt(i * 20, i, COLUMN_COUNT);
		_listView.setItemInt(i * 10, i, COLUMN_PACKAGE);
		_listView.setItemInt(i * 5, i, COLUMN_NEEDED);
		_listView.setItemText(TEXT("10.02"), i, COLUMN_RETAILPRICE);
		_listView.setItemText(TEXT("8.50"), i, COLUMN_WHOLESALEPRICE);
	}
}


void StorageWindow::onResize(LPARAM lParam)
{
	_cX = LOWORD(lParam);
	_cY = HIWORD(lParam);
	WindowControls::setWindowSize(_listView.getListHandle(), _cX, _cY);
}
