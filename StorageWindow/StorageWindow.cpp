#include "StorageWindow.h"
//#include "StorageWindow.h"
//
//LRESULT StorageWindow::MessageHandler(UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	switch (msg)
//	{
//	case WM_CREATE:
//	{
//		initilaizeWindow();
//	}
//	break;
//
//	case WM_SIZE:
//	{
//		const int cX = LOWORD(lParam);
//		const int cY = HIWORD(lParam);
//
//		WindowControls::setWindowSize(_list, cX, cY);
//	}
//	return DefMDIChildProc(_hWnd, msg, wParam, lParam);
//
//	default:
//		return DefMDIChildProc(_hWnd, msg, wParam, lParam);
//	}
//
//	return 0;
//}
//
//void StorageWindow::initilaizeWindow()
//{
//	RECT rc;
//	GetClientRect(_hWnd, &rc);
//	_list = CList::createList(_hWnd, 0, 0, rc.right - rc.left, rc.bottom - rc.top, ID_STORAGE_LIST);
//	CList::setTxtBkColor(_list, RGB(179, 248, 255));
//	CList::setBkColor(_list, RGB(179, 248, 255));
//	CList::insertColumn(_list, CODE_COLUMN, "Code", 0x80);
//	CList::insertColumn(_list, NAME_COLUMN, "Name", 0x120);
//	CList::insertColumn(_list, DESCR_COLUMN, "Description", 0x80);
//	CList::insertColumn(_list, COUNT_COLUMN, "Count", 0x80);
//	CList::insertColumn(_list, PACKAGE_COLUMN, "Package", 0x80);
//	CList::insertColumn(_list, NEEDED_COLUMN, "Needed", 0x80);
//	CList::insertColumn(_list, RETAILPRICE_COLUMN, "Retail Price", 0x80);
//	CList::insertColumn(_list, WHOLESALE_COLUMN, "Wholesale Price", 0x80);
//	CList::setFullRowSelect(_list);
//
//	for (size_t i = 0; i < 200; ++i)
//	{
//		CList::insertItem(_list, 9999999);
//		CList::setItemText(_list, "1000", i, CODE_COLUMN);
//		CList::setItemText(_list, "Visokootporni lanac FI 10", i, NAME_COLUMN);
//		CList::setItemText(_list, "Lanac FI 10", i, DESCR_COLUMN);
//		CList::setItemText(_list, "10000", i, COUNT_COLUMN);
//		CList::setItemText(_list, "2000", i, PACKAGE_COLUMN);
//		CList::setItemText(_list, "5000", i, NEEDED_COLUMN);
//		CList::setItemText(_list, "10.02", i, RETAILPRICE_COLUMN);
//		CList::setItemText(_list, "8.50", i, WHOLESALE_COLUMN);
//	}
//}

LRESULT StorageWindow::MessageHandler(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		delete this;
		StorageWindow::removeInstance();
		return DefMDIChildProc(_mHwnd, msg, wParam, lParam);

	default:
		return DefMDIChildProc(_mHwnd, msg, wParam, lParam);
	}

	return 0;
}
