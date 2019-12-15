#include "StorageWindow.h"

LRESULT CALLBACK Storage::StorageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND edit;

	switch (msg)
	{
	case WM_CREATE:
	{
		Storage::initilaizeWindow(hWnd);
	}
	break;

	case WM_SIZE:
	{
		const int cX = LOWORD(lParam);
		const int cY = HIWORD(lParam);

		WindowControls::setWindowSize(GetDlgItem(hWnd, ID_STORAGE_LIST), cX, cY);
	}
	return DefMDIChildProc(hWnd, msg, wParam, lParam);

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

	default:
		return DefMDIChildProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

void Storage::initilaizeWindow(const HWND & hWnd)
{
	RECT rc;
	GetClientRect(hWnd, &rc);
	const HWND list = CList::createList(hWnd, 0, 0, rc.right - rc.left, rc.bottom - rc.top, ID_STORAGE_LIST);
	CList::setTxtBkColor(list, RGB(11, 98, 135));
	CList::setBkColor(list, RGB(11, 98, 135));
	CList::insertColumn(list, CODE_COLUMN, "Code", 0x80);
	CList::insertColumn(list, NAME_COLUMN, "Name", 0x120);
	CList::insertColumn(list, DESCR_COLUMN, "Description", 0x80);
	CList::insertColumn(list, COUNT_COLUMN, "Count", 0x80);
	CList::insertColumn(list, PACKAGE_COLUMN, "Package", 0x80);
	CList::insertColumn(list, NEEDED_COLUMN, "Needed", 0x80);
	CList::insertColumn(list, RETAILPRICE_COLUMN, "Retail Price", 0x80);
	CList::insertColumn(list, WHOLESALE_COLUMN, "Wholesale Price", 0x80);
	CList::setFullRowSelect(list);

	for (size_t i = 0; i < 200; ++i)
	{
		CList::insertItem(list, 9999999);
		CList::setItemText(list, "1000", i, CODE_COLUMN);
		CList::setItemText(list, "Visokootporni lanac FI 10", i, NAME_COLUMN);
		CList::setItemText(list, "Lanac FI 10", i, DESCR_COLUMN);
		CList::setItemText(list, "10000", i, COUNT_COLUMN);
		CList::setItemText(list, "2000", i, PACKAGE_COLUMN);
		CList::setItemText(list, "5000", i, NEEDED_COLUMN);
		CList::setItemText(list, "10.02", i, RETAILPRICE_COLUMN);
		CList::setItemText(list, "8.50", i, WHOLESALE_COLUMN);
	}
}
