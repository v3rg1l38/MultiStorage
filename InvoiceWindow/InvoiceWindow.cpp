#include "InvoiceWindow.h"
#include <math.h>

LRESULT InvoiceWindow::MDICProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
		onPaint();
		break;

	case WM_CLOSE:
	{
		MenuControl mc;
		mc.EnableMenu(_mHwnd, MENU_INVOICE, MENU_INVOICE_LIST);
		DestroyWindow(_mHwnd);
	}
	return 0;

	case WM_MDIACTIVATE:
	{
		MenuControl mc;
		mc.DisableMenu(_mHwnd, MENU_INVOICE, MENU_INVOICE_LIST);
	}
	break;

	case WM_CREATE:
		onCreate();
		break;
	case WM_SIZE:
		_cX = LOWORD(lParam);
		_cY = HIWORD(lParam);
		onResize();
		return DefMDIChildProc(_mHwnd, msg, wParam, lParam);

	default:
		return DefMDIChildProc(_mHwnd, msg, wParam, lParam);
	}

	return 0;
}

void InvoiceWindow::onCreate()
{
	RECT rc;
	GetClientRect(_mHwnd, &rc);
	const int tableStart = _cY;
	_tablePos = tableStart;
	_startTablePos = tableStart;
	_columns = { 0, 120, 440, 500, 580, 660, 740 };

	for (size_t i = 0; i < 14; ++i)
	{
		_editBoxes.emplace_back(_mHwnd, TEXT(""), 0, tableStart + (20 * i), 120, 20); // Code
		_editBoxes.emplace_back(_mHwnd, TEXT(""), 120, tableStart + (20 * i), 320, 20); // Name
		_editBoxes.emplace_back(_mHwnd, TEXT(""), 440, tableStart + (20 * i), 60, 20); // Unit
		_editBoxes.emplace_back(_mHwnd, TEXT(""), 500, tableStart + (20 * i), 80, 20); // Count
		_editBoxes.emplace_back(_mHwnd, TEXT(""), 580, tableStart + (20 * i), 80, 20); // Retail price
		_editBoxes.emplace_back(_mHwnd, TEXT(""), 660, tableStart + (20 * i), 80, 20); // Wholesale price
		_editBoxes.emplace_back(_mHwnd, TEXT(""), 740, tableStart + (20 * i), 80, 20); // Discount
	}

}

void InvoiceWindow::onPaint()
{
	PAINTSTRUCT ps;
	RECT rc;
	HBRUSH prodBack = CreateSolidBrush(RGB(5, 193, 245));
	HBRUSH cliBack = CreateSolidBrush(RGB(107, 187, 209));

	HDC hdc = BeginPaint(_mHwnd, &ps);
	GetClientRect(_mHwnd, &rc);

	FillRect(hdc, &rc, reinterpret_cast<HBRUSH>(GetStockObject(LTGRAY_BRUSH)));

	SelectObject(hdc, prodBack);
	Rectangle(hdc, _columns.at(0), _tablePos - 22, _columns.at(6) + 80, _tablePos);

	SelectObject(hdc, cliBack);
	Rectangle(hdc, rc.left, rc.top, rc.right, _tablePos - 20);

	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, _columns.at(0), _tablePos - 20, TEXT("Code"), lstrlen(TEXT("Code")));
	TextOut(hdc, _columns.at(1), _tablePos - 20, TEXT("Name"), lstrlen(TEXT("Name")));
	TextOut(hdc, _columns.at(2), _tablePos - 20, TEXT("Unit"), lstrlen(TEXT("Unit")));
	TextOut(hdc, _columns.at(3), _tablePos - 20, TEXT("Count"), lstrlen(TEXT("Count")));
	TextOut(hdc, _columns.at(4), _tablePos - 20, TEXT("Retail Pr."), lstrlen(TEXT("Retail Pr.")));
	TextOut(hdc, _columns.at(5), _tablePos - 20, TEXT("Wholes Pr."), lstrlen(TEXT("Wholes Pr.")));
	TextOut(hdc, _columns.at(6), _tablePos - 20, TEXT("Discount"), lstrlen(TEXT("Discount")));

	DeleteObject(prodBack);
	DeleteObject(cliBack);
	EndPaint(_mHwnd, &ps);
}

void InvoiceWindow::onResize()
{
	RECT rc;
	GetClientRect(_mHwnd, &rc);
	const int startOfTable = rc.bottom - 160;
	_tablePos = startOfTable;

	for (size_t i = 0; i < _editBoxes.size(); ++i)
	{
	const int y = _editBoxes.at(i).getPosY();
	const int diff = (y - _startTablePos);
	const int difM = diff / 20;

	SetWindowPos(_editBoxes.at(i).getHandle(),
		NULL,
		_editBoxes.at(i).getPosX(),
		startOfTable + (difM * 20),
		0,
		0,
		SWP_NOSIZE);
	}

}
