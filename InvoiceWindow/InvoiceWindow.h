#pragma once
#define UNICODE

#include <Windows.h>
#include "../WindowManager/WindowManager.h"

#define INVOICE_OIB 8000
#define INVOICE_CLIENT_NAME 8001
#define INVOICE_NUMBER 8002

class InvoiceWindow : public BaseMDIChild<InvoiceWindow>
{
public:
	InvoiceWindow() {}
	virtual LRESULT CALLBACK MDICProc(UINT msg, WPARAM wParam, LPARAM lParam);

private:
	std::vector<Edit> _editBoxes;
	int _tablePos;
	void onCreate();
	void onPaint();
	void onResize();
	InvoiceWindow(const InvoiceWindow &) = delete;
	InvoiceWindow & operator=(const InvoiceWindow &) = delete;
};
