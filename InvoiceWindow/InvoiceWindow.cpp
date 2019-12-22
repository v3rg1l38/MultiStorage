#include "InvoiceWindow.h"

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

	default:
		return DefMDIChildProc(_mHwnd, msg, wParam, lParam);
	}

	return 0;
}

void InvoiceWindow::onCreate()
{
	Edit oib;
	oib.createEdit(_mHwnd, TEXT(""), 50, 40, 120, 25, reinterpret_cast<HMENU>(INVOICE_OIB));
	Edit client;
	client.createEdit(_mHwnd, TEXT(""), 50, 85, 120, 25, reinterpret_cast<HMENU>(INVOICE_CLIENT_NAME));
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
