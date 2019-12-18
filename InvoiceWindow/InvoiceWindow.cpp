#include "InvoiceWindow.h"

LRESULT InvoiceWindow::MDICProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	default:
		return DefMDIChildProc(_mHwnd, msg, wParam, lParam);
	}

	return 0;
}

void InvoiceWindow::onCreate()
{
	RECT rc;
	HDC hdc = GetDC(_mHwnd);
	GetClientRect(_mHwnd, &rc);
	HBRUSH newBrush = CreateSolidBrush(RGB(232, 190, 118));
	FillRect(hdc, &rc, newBrush);
	DeleteObject(newBrush);
	ReleaseDC(_mHwnd, hdc);

	int startY = 5;
	for (unsigned int i = 0; i < 8; ++i)
	{
	CreateWindowEx(0,
		"EDIT",
		"",
		ES_AUTOVSCROLL | WS_CHILD | WS_VISIBLE,
		5,
		startY + (50 * i),
		160,
		30,
		_mHwnd,
		NULL,
		GetModuleHandle(NULL),
		NULL);
	}
	for (unsigned int i = 0; i < 8; ++i)
	{
		CreateWindowEx(0,
			"EDIT",
			"",
			ES_AUTOVSCROLL | WS_CHILD | WS_VISIBLE,
			200,
			startY + (50 * i),
			160,
			30,
			_mHwnd,
			NULL,
			GetModuleHandle(NULL),
			NULL);
	}
}