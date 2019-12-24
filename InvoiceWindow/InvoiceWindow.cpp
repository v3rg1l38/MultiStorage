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

	case WM_COMMAND:
	{
		switch (HIWORD(wParam))
		{
			/*	idEditCtrl = (int) LOWORD(wParam); // identifier of edit control
				wNotifyCode = HIWORD(wParam); // notification code
				hwndEditCtrl = (HWND) lParam; // handle of edit control
			*/
		case EN_KILLFOCUS:
			break;
		}
	}
	break;

	case WM_MDIACTIVATE:
	{
		MenuControl mc;
		mc.DisableMenu(_mHwnd, MENU_INVOICE, MENU_INVOICE_LIST);
	}
	break;

	case WM_CTLCOLORSTATIC:
	{
		HDC hdc = reinterpret_cast<HDC>(wParam);
		SetBkMode(hdc, TRANSPARENT);
	}
	return reinterpret_cast<int>(GetStockObject(NULL_BRUSH));

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
	RECT rc;
	GetClientRect(_mHwnd, &rc);
	_tablePos = rc.bottom - 160;
	_columns = { 0, 120, 440, 500, 580, 660, 740 };
	createInputFields();
}

void InvoiceWindow::onPaint()
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(_mHwnd, &ps);

	FillRect(hdc, &ps.rcPaint, _cliBack);
	SelectObject(hdc, _prodBack);
	Rectangle(hdc, 0, _tablePos - 20 - _vertPos, ps.rcPaint.right, _tablePos + 20 - _vertPos);
	EndPaint(_mHwnd, &ps);
}

void InvoiceWindow::onResize()
{
	if(_cY)
		setVertScroll(_mHwnd, 0, _cY + _editBoxes.size() / 2, 20 / _cY);
}

void InvoiceWindow::createInputFields()
{
	RECT rc;
	GetClientRect(_mHwnd, &rc);

	// Product fields
	for(int i = 0; i < 20; ++i)
	{
		_editBoxes.push_back(Edit(_mHwnd, TEXT(""), 
			_columns.at(0), _tablePos + (20 * i), 120, 20, reinterpret_cast<HMENU>(COLUMN_ID_CODE + i))); // Code
		_editBoxes.push_back(Edit(_mHwnd, TEXT(""),
			_columns.at(1), _tablePos + (20 * i), 320, 20, reinterpret_cast<HMENU>(COLUMN_ID_NAME + i))); // Name
		_editBoxes.push_back(Edit(_mHwnd, TEXT(""), 
			_columns.at(2), _tablePos + (20 * i), 60, 20, reinterpret_cast<HMENU>(COLUMN_ID_UNIT + i))); // Unit
		_editBoxes.push_back(Edit(_mHwnd, TEXT(""),
			_columns.at(3), _tablePos + (20 * i), 80, 20, reinterpret_cast<HMENU>(COLUMN_ID_COUNT + i))); // Count
		_editBoxes.push_back(Edit(_mHwnd, TEXT(""), 
			_columns.at(4), _tablePos + (20 * i), 80, 20, reinterpret_cast<HMENU>(COLUMN_ID_RETAILPR + i))); // Retail price
		_editBoxes.push_back(Edit(_mHwnd, TEXT(""),
			_columns.at(5), _tablePos + (20 * i), 80, 20, reinterpret_cast<HMENU>(COLUMN_ID_WHOLEPR + i))); // Wholesale price
		_editBoxes.push_back(Edit(_mHwnd, TEXT(""),
			_columns.at(6), _tablePos + (20 * i), 80, 20, reinterpret_cast<HMENU>(COLUMN_ID_DISCOUNT + i))); // Discount
	}

	StaticText sOib(_mHwnd, TEXT("OIB"), 20, 20, 120, 20);
	Edit eOib(_mHwnd, TEXT(""), 10, 40, 120, 20, reinterpret_cast<HMENU>(INPUT_CLIENT_OIB));
	StaticText sName(_mHwnd, TEXT("Name"), 20, 65, 120, 20);
	Edit eName(_mHwnd, TEXT(""), 10, 85, 280, 20, reinterpret_cast<HMENU>(INPUT_CLIENT_NAME));
	StaticText sInvNumber(_mHwnd, TEXT("Invoice Number"), rc.right - 140, 20, 120, 20);
	Edit eInvNumber(_mHwnd, TEXT(""), rc.right - 140, 40, 120, 20, reinterpret_cast<HMENU>(INPUT_INVOICE_NUMBER));
	StaticText sDate(_mHwnd, TEXT("Date"), rc.right - 140, 60, 120, 20);
	Edit eDate(_mHwnd, TEXT(""), rc.right - 140, 80, 120, 20, reinterpret_cast<HMENU>(INPUT_INVOICE_DATE));
	StaticText sPayment(_mHwnd, TEXT("Payment Method"), rc.right - 140, 105, 120, 20);
	Edit ePayment(_mHwnd, TEXT(""), rc.right - 140, 125, 120, 20, reinterpret_cast<HMENU>(INPUT_INVOICE_PAYMENT));

	StaticText sCode(_mHwnd, TEXT("Code"), 0, _tablePos - 20, 120, 20);
	StaticText sInvName(_mHwnd, TEXT("Name"), _columns.at(1), _tablePos - 20, 120, 20);
	StaticText sUnit(_mHwnd, TEXT("Unit"), _columns.at(2), _tablePos - 20, 120, 20);
	StaticText sCount(_mHwnd, TEXT("Count"), _columns.at(3), _tablePos - 20, 120, 20);
	StaticText sRetail(_mHwnd, TEXT("Retail Pr."), _columns.at(4), _tablePos - 20, 120, 20);
	StaticText sWholes(_mHwnd, TEXT("Wholes Pr."), _columns.at(5), _tablePos - 20, 120, 20);
	StaticText sDiscount(_mHwnd, TEXT("Discount"), _columns.at(6), _tablePos - 20, 120, 20);
}
