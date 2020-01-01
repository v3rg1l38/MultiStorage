#pragma once
#define UNICODE

#include <Windows.h>

template <class DLG>
class DlgBase
{
public:
	static INT_PTR CALLBACK DlgBaseProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void createDialog(const int & templateName, const HWND & parent);

protected:
	HWND _hDlg;
	virtual INT_PTR CALLBACK DlgProc(UINT msg, WPARAM wParam, LPARAM lParam) = 0;
};

template <class DLG>
INT_PTR CALLBACK DlgBase<DLG>::DlgBaseProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	DLG *pData = nullptr;

	if (msg == WM_INITDIALOG)
	{
		pData = reinterpret_cast<DLG*>(lParam);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pData));
		pData->_hDlg = hWnd;
		pData->DlgProc(msg, wParam, lParam);
		return 1;
	}
	else
		pData = reinterpret_cast<DLG*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	if (pData)
		return pData->DlgProc(msg, wParam, lParam);
	else
		return 0;
}

template <class DLG>
void DlgBase<DLG>::createDialog(const int & templateName, const HWND & parent)
{
	DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(templateName), parent, DlgBaseProc, reinterpret_cast<LPARAM>(this));
}