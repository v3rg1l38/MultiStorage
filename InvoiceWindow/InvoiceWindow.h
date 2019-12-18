#pragma once

#include <Windows.h>
#include "../ListControls/CList.h"
#include "../WindowManager/WindowManager.h"

class InvoiceWindow : public BaseMDIChild<InvoiceWindow>
{
public:
	virtual LRESULT CALLBACK MDICProc(UINT msg, WPARAM wParam, LPARAM lParam);
	virtual void onCreate();
};
