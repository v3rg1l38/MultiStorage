#include "StorageWindow.h"

LRESULT StorageWindow::MDICProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{

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
	CList::insertColumn(_listHandle, CODE_COLUMN, "Code", 0x80);
	CList::insertColumn(_listHandle, NAME_COLUMN, "Name", 0x120);
	CList::insertColumn(_listHandle, DESCR_COLUMN, "Description", 0x80);
	CList::insertColumn(_listHandle, COUNT_COLUMN, "Count", 0x80);
	CList::insertColumn(_listHandle, PACKAGE_COLUMN, "Package", 0x80);
	CList::insertColumn(_listHandle, NEEDED_COLUMN, "Needed", 0x80);
	CList::insertColumn(_listHandle, RETAILPRICE_COLUMN, "Retail Price", 0x80);
	CList::insertColumn(_listHandle, WHOLESALE_COLUMN, "Wholesale Price", 0x80);
	CList::setFullRowSelect(_listHandle);

	for (size_t i = 0; i < 200; ++i)
	{
		CList::insertItem(_listHandle, 9999999);
		CList::setItemInt(_listHandle, i + 1, i, CODE_COLUMN);
		CList::setItemText(_listHandle, "Visokootporni lanac FI 10", i, NAME_COLUMN);
		CList::setItemText(_listHandle, "Lanac FI 10", i, DESCR_COLUMN);
		CList::setItemInt(_listHandle, i * 20, i, COUNT_COLUMN);
		CList::setItemInt(_listHandle, i * 10, i, PACKAGE_COLUMN);
		CList::setItemInt(_listHandle, i * 5, i, NEEDED_COLUMN);
		CList::setItemText(_listHandle, "10.02", i, RETAILPRICE_COLUMN);
		CList::setItemText(_listHandle, "8.50", i, WHOLESALE_COLUMN);
	}
}


void StorageWindow::onResize(LPARAM lParam)
{
	_cX = LOWORD(lParam);
	_cY = HIWORD(lParam);
	WindowControls::setWindowSize(_listHandle, _cX, _cY);
}
