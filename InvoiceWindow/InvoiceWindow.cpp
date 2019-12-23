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
		DeleteObject(_prodBack);
		DeleteObject(_cliBack);
		DestroyWindow(_mHwnd);
	}
	return 0;

	case WM_MDIACTIVATE:
	{
		MenuControl mc;
		mc.DisableMenu(_mHwnd, MENU_INVOICE, MENU_INVOICE_LIST);
	}
	break;

	case WM_MOUSEWHEEL:
		onMouseWheelScroll(_mHwnd, wParam);
		break;

	case WM_CREATE:
		onCreate();
	
	case WM_SETTINGCHANGE:
		onSettingChange();
		break;

	case WM_VSCROLL:
		onVertScroll(_mHwnd, wParam);
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
	_prodBack = CreateSolidBrush(RGB(5, 193, 245));
	_cliBack = CreateSolidBrush(RGB(107, 187, 209));
	LONG lStyle = GetWindowLongPtr(_mHwnd, GWL_STYLE);
	lStyle &= ~(WS_THICKFRAME | WS_MAXIMIZEBOX);
	SetWindowLongPtr(_mHwnd, GWL_STYLE, lStyle);

	_tablePos = _cY;
	_columns = { 0, 120, 440, 500, 580, 660, 740 };
	createInputFields();

}

void InvoiceWindow::onPaint()
{
	PAINTSTRUCT ps;
	RECT rc;
	GetClientRect(_mHwnd, &rc);
	HDC hdc = BeginPaint(_mHwnd, &ps);

	SelectObject(hdc, _prodBack);
	Rectangle(hdc, _columns.at(0), (_tablePos - 22) - _vertPos, _columns.at(6) + 80, _tablePos - _vertPos);

	SelectObject(hdc, _cliBack);
	Rectangle(hdc, 0, 0, _cX, _tablePos - 20 - _vertPos);

	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, _columns.at(0), _tablePos - 20 - _vertPos, TEXT("Code"), lstrlen(TEXT("Code")));
	TextOut(hdc, _columns.at(1), _tablePos - 20 - _vertPos, TEXT("Name"), lstrlen(TEXT("Name")));
	TextOut(hdc, _columns.at(2), _tablePos - 20 - _vertPos, TEXT("Unit"), lstrlen(TEXT("Unit")));
	TextOut(hdc, _columns.at(3), _tablePos - 20 - _vertPos, TEXT("Count"), lstrlen(TEXT("Count")));
	TextOut(hdc, _columns.at(4), _tablePos - 20 - _vertPos, TEXT("Retail Pr."), lstrlen(TEXT("Retail Pr.")));
	TextOut(hdc, _columns.at(5), _tablePos - 20 - _vertPos, TEXT("Wholes Pr."), lstrlen(TEXT("Wholes Pr.")));
	TextOut(hdc, _columns.at(6), _tablePos - 20 - _vertPos, TEXT("Discount"), lstrlen(TEXT("Discount")));

	EndPaint(_mHwnd, &ps);
}

void InvoiceWindow::onResize()
{
	RECT rc;
	GetClientRect(_mHwnd, &rc);
	const int startOfTable = rc.bottom - 160;
	_tablePos = startOfTable;

	if(_cY)
		setVertScroll(_mHwnd, 0, _cY + _editBoxes.size() / 2, 20 / _cY);

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

void InvoiceWindow::createInputFields()
{
	// Product fields
	for (int i = 20; i >= 0; --i)
	{
		_editBoxes.push_back(Edit(_mHwnd, TEXT(""),
			_columns.at(6), _tablePos + (20 * i), 80, 20, reinterpret_cast<HMENU>(COLUMN_ID_DISCOUNT + i))); // Discount
		_editBoxes.push_back(Edit(_mHwnd, TEXT(""),
			_columns.at(5), _tablePos + (20 * i), 80, 20, reinterpret_cast<HMENU>(COLUMN_ID_WHOLEPR + i))); // Wholesale price
		_editBoxes.push_back(Edit(_mHwnd, TEXT(""), 
			_columns.at(4), _tablePos + (20 * i), 80, 20, reinterpret_cast<HMENU>(COLUMN_ID_RETAILPR + i))); // Retail price
		_editBoxes.push_back(Edit(_mHwnd, TEXT(""),
			_columns.at(3), _tablePos + (20 * i), 80, 20, reinterpret_cast<HMENU>(COLUMN_ID_COUNT + i))); // Count
		_editBoxes.push_back(Edit(_mHwnd, TEXT(""), 
			_columns.at(2), _tablePos + (20 * i), 60, 20, reinterpret_cast<HMENU>(COLUMN_ID_UNIT + i))); // Unit
		_editBoxes.push_back(Edit(_mHwnd, TEXT(""),
			_columns.at(1), _tablePos + (20 * i), 320, 20, reinterpret_cast<HMENU>(COLUMN_ID_NAME + i))); // Name
		_editBoxes.push_back(Edit(_mHwnd, TEXT(""), 
			_columns.at(0), _tablePos + (20 * i), 120, 20, reinterpret_cast<HMENU>(COLUMN_ID_CODE + i))); // Code
	}

	Edit p1(_mHwnd, TEXT(""), 10, 20, 120, 20);
}
