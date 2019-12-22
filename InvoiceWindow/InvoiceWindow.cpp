#include "InvoiceWindow.h"
#include <math.h>

LRESULT InvoiceWindow::MDICProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
		onPaint();
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

	for (size_t i = 0; i < 8; ++i)
	{
		_editBoxes.emplace_back(_mHwnd, TEXT(""), 0, tableStart + (20 * i), 120, 20); // Code
		_editBoxes.emplace_back(_mHwnd, TEXT(""), 120, tableStart + (20 * i), 320, 20); // Name
		_editBoxes.emplace_back(_mHwnd, TEXT(""), 440, tableStart + (20 * i), 60, 20); // Unit
		_editBoxes.emplace_back(_mHwnd, TEXT(""), 500, tableStart + (20 * i), 80, 20); // Count
	}
}

void InvoiceWindow::onPaint()
{
	PAINTSTRUCT ps;
	RECT rc;
	HDC hdc = BeginPaint(_mHwnd, &ps);
	GetClientRect(_mHwnd, &rc);
	FillRect(hdc, &rc, reinterpret_cast<HBRUSH>(GetStockObject(LTGRAY_BRUSH)));
	EndPaint(_mHwnd, &ps);
}

void InvoiceWindow::onResize()
{
	RECT rc;
	GetClientRect(_mHwnd, &rc);
	const int startOfTable = rc.bottom - 180;

	for (size_t i = 0; i < _editBoxes.size(); ++i)
	{
	int y = _editBoxes.at(i).getPosY();
	int diff = (y - _tablePos);
	int difM = diff / 20;

	SetWindowPos(_editBoxes.at(i).getHandle(),
		NULL,
		_editBoxes.at(i).getPosX(),
		startOfTable + (difM * 20),
		0,
		0,
		SWP_NOSIZE);
	}

}
