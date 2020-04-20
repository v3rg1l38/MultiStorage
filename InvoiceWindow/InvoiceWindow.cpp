#include "InvoiceWindow.h"

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
		case EN_KILLFOCUS:
			if (static_cast<int>(LOWORD(wParam)) < 200)
				searchForData(wParam, lParam);
			break;
		}
	}
	break;

	//case WM_COMMAND:
	//{
	//	switch (HIWORD(wParam))
	//	{
	//		/*	idEditCtrl = (int) LOWORD(wParam); // identifier of edit control
	//			wNotifyCode = HIWORD(wParam); // notification code
	//			hwndEditCtrl = (HWND) lParam; // handle of edit control
	//		*/
	//	case EN_KILLFOCUS:
	//	{
	//		lstrcpy
	//	}
	//		break;
	//	}
	//}
	//break;

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
		onVertScroll(_mHwnd, wParam, _charHeight);
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
	HDC hdc = GetDC(_mHwnd);
	GetTextMetrics(hdc, &_tMetrics);
	_charHeight = _tMetrics.tmHeight + _tMetrics.tmExternalLeading;
	_charWidth = _tMetrics.tmAveCharWidth;
	ReleaseDC(_mHwnd, hdc);

	_prodBack = CreateSolidBrush(RGB(5, 193, 245));
	_cliBack = CreateSolidBrush(RGB(107, 187, 209));
	_tablePos = rc.bottom - 160;
	_columns = { 0, 120, 440, 500, 580, 660, 740 };

	createInputFields();
}

void InvoiceWindow::onPaint()
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(_mHwnd, &ps);
	FillRect(hdc, &ps.rcPaint, _cliBack);
	EndPaint(_mHwnd, &ps);
}

void InvoiceWindow::onResize()
{
	if (_cY <= 0)
		return;

	const int diff = _tablePos + (_rows * 20);
	const int move = (diff - _cY) / _charHeight;
	if (move >= 0)
	{
		setVertScroll(_mHwnd, 0, move + 5, _charHeight / _cY);
		_scrollable = true;
	}
	else
	{
		setVertScroll(_mHwnd, 0, 0, _charHeight / _cY);
		_scrollable = false;
	}
}

void InvoiceWindow::searchForData(WPARAM wParam, LPARAM lParam)
{
	std::wstring code = WindowControls::getEditText(reinterpret_cast<HWND>(lParam));

	if (code.length() <= 0)
		return;

	// Diff between Code edit box and other boxes
	const int codeBox = static_cast<int>(LOWORD(wParam));
	const int name = 100;
	const int unit = 200;
	const int count = 300;
	const int retpr = 400;
	const int wholepr = 500;
	const int discount = 600;

	int index = -1;

	for (size_t i = 0; i < _prods->size(); ++i)
	{
		if (lstrcmp(code.c_str(), _prods->at(i).getCCode()) == 0)
		{
			index = i;
			break;
		}
	}

	if (index == -1)
		return;

	TCHAR rPrice[1024] = L"";
	TCHAR wPrice[1024] = L"";
	_snwprintf_s(rPrice, 1024, L"%.2f", _prods->at(index).getRetailPrice());
	_snwprintf_s(wPrice, 1024, L"%.2f", _prods->at(index).getWholesalePrice());
	SetDlgItemText(_mHwnd, codeBox + name, _prods->at(index).getCName());
	SetDlgItemText(_mHwnd, codeBox + unit, _prods->at(index).getCUnit());
	SetDlgItemText(_mHwnd, codeBox + retpr, rPrice);
	SetDlgItemText(_mHwnd, codeBox + wholepr, wPrice);
}

void InvoiceWindow::createInputFields()
{
	RECT rc;
	GetClientRect(_mHwnd, &rc);
	_rows = 10;

	// Product fields
	for(int i = 0; i < _rows; ++i)
	{
		Edit(_mHwnd, TEXT(""), 
			_columns.at(0), _tablePos + (20 * i), 120, 20, reinterpret_cast<HMENU>(COLUMN_ID_CODE + i)); // Code
		Edit(_mHwnd, TEXT(""),
			_columns.at(1), _tablePos + (20 * i), 320, 20, reinterpret_cast<HMENU>(COLUMN_ID_NAME + i)); // Name
		Edit(_mHwnd, TEXT(""),
			_columns.at(2), _tablePos + (20 * i), 60, 20, reinterpret_cast<HMENU>(COLUMN_ID_UNIT + i)); // Unit
		Edit(_mHwnd, TEXT(""),
			_columns.at(3), _tablePos + (20 * i), 80, 20, reinterpret_cast<HMENU>(COLUMN_ID_COUNT + i)); // Count
		Edit(_mHwnd, TEXT(""),
			_columns.at(4), _tablePos + (20 * i), 80, 20, reinterpret_cast<HMENU>(COLUMN_ID_RETAILPR + i)); // Retail price
		Edit(_mHwnd, TEXT(""),
			_columns.at(5), _tablePos + (20 * i), 80, 20, reinterpret_cast<HMENU>(COLUMN_ID_WHOLEPR + i)); // Wholesale price
		Edit(_mHwnd, TEXT(""),
			_columns.at(6), _tablePos + (20 * i), 80, 20, reinterpret_cast<HMENU>(COLUMN_ID_DISCOUNT + i)); // Discount
	}

	StaticText(_mHwnd, TEXT("OIB"), 20, 20, 120, 20);
	Edit(_mHwnd, TEXT(""), 10, 40, 120, 20, reinterpret_cast<HMENU>(INPUT_CLIENT_OIB));
	StaticText(_mHwnd, TEXT("Name"), 20, 65, 120, 20);
	Edit(_mHwnd, TEXT(""), 10, 85, 280, 20, reinterpret_cast<HMENU>(INPUT_CLIENT_NAME));
	StaticText(_mHwnd, TEXT("Invoice Number"), rc.right - 140, 20, 120, 20);
	Edit(_mHwnd, TEXT(""), rc.right - 140, 40, 120, 20, reinterpret_cast<HMENU>(INPUT_INVOICE_NUMBER));
	StaticText(_mHwnd, TEXT("Date"), rc.right - 140, 60, 120, 20);
	Edit(_mHwnd, TEXT(""), rc.right - 140, 80, 120, 20, reinterpret_cast<HMENU>(INPUT_INVOICE_DATE));
	StaticText(_mHwnd, TEXT("Payment Method"), rc.right - 140, 105, 120, 20);
	Edit(_mHwnd, TEXT(""), rc.right - 140, 125, 120, 20, reinterpret_cast<HMENU>(INPUT_INVOICE_PAYMENT));

	StaticText(_mHwnd, TEXT("Code"), 0, _tablePos - 20, 120, 20);
	StaticText(_mHwnd, TEXT("Name"), _columns.at(1), _tablePos - 20, 120, 20);
	StaticText(_mHwnd, TEXT("Unit"), _columns.at(2), _tablePos - 20, 120, 20);
	StaticText(_mHwnd, TEXT("Count"), _columns.at(3), _tablePos - 20, 120, 20);
	StaticText(_mHwnd, TEXT("Retail Pr."), _columns.at(4), _tablePos - 20, 120, 20);
	StaticText(_mHwnd, TEXT("Wholes Pr."), _columns.at(5), _tablePos - 20, 120, 20);
	StaticText(_mHwnd, TEXT("Discount"), _columns.at(6), _tablePos - 20, 120, 20);
	StaticText(_mHwnd, TEXT("INVOICE"), rc.right / 2 - 50, 20, 120, 30);
}
