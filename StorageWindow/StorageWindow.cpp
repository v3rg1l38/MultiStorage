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
	return 0;

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
	_listView.insertColumn(COLUMN_CODE, Localization::getLocalString(L"STORAGE_COLUMN_CODE"), 0x80);
	_listView.insertColumn(COLUMN_NAME, Localization::getLocalString(L"STORAGE_COLUMN_NAME"), 0x120);
	_listView.insertColumn(COLUMN_UNIT, Localization::getLocalString(L"STORAGE_COLUMN_UNIT"), 0x80);
	_listView.insertColumn(COLUMN_COUNT, Localization::getLocalString(L"STORAGE_COLUMN_COUNT"), 0x80);
	_listView.insertColumn(COLUMN_PACKAGE, Localization::getLocalString(L"STORAGE_COLUMN_PACKAGE"), 0x80);
	_listView.insertColumn(COLUMN_NEEDED, Localization::getLocalString(L"STORAGE_COLUMN_NEEDED"), 0x80);
	_listView.insertColumn(COLUMN_RETAILPRICE, Localization::getLocalString(L"STORAGE_COLUMN_RETAILPR"), 0x80);
	_listView.insertColumn(COLUMN_WHOLESALEPRICE, Localization::getLocalString(L"STORAGE_COLUMN_WHOLEPR"), 0x80);
	_listView.setFullRowSelect();

	SetWindowTheme(_listView.getListHandle(), L"DarkMode_Explorer", NULL);

	for (size_t i = 0; i < _prods->size(); ++i)
	{
		_listView.insertItem(99999999);
		_listView.setItemText(_prods->at(i).getCCode(), i, COLUMN_CODE);
		_listView.setItemText(_prods->at(i).getCName(), i, COLUMN_NAME);
		_listView.setItemText(_prods->at(i).getCUnit(), i, COLUMN_UNIT);
		_listView.setItemInt(_prods->at(i).getCount(), i, COLUMN_COUNT);
		_listView.setItemInt(_prods->at(i).getPackage(), i, COLUMN_PACKAGE);
		_listView.setItemInt(_prods->at(i).getNeeded(), i, COLUMN_NEEDED);
		_listView.setItemDouble(_prods->at(i).getRetailPrice(), i, COLUMN_RETAILPRICE);
		_listView.setItemDouble(_prods->at(i).getWholesalePrice(), i, COLUMN_WHOLESALEPRICE);
	}


}


void StorageWindow::onResize(LPARAM lParam)
{
	_cX = LOWORD(lParam);
	_cY = HIWORD(lParam);
	WindowControls::setWindowSize(_listView.getListHandle(), _cX, _cY);
}
