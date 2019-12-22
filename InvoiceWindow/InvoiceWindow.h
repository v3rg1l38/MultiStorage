#pragma once
#define UNICODE

#include <Windows.h>
#include "../WindowManager/WindowManager.h"

class InvoiceWindow : public BaseMDIChild<InvoiceWindow>
{
public:
	InvoiceWindow() {}
	virtual LRESULT CALLBACK MDICProc(UINT msg, WPARAM wParam, LPARAM lParam);
	void onCreate();

private:
	InvoiceWindow(const InvoiceWindow &) = delete;
	InvoiceWindow & operator=(const InvoiceWindow &) = delete;
};
