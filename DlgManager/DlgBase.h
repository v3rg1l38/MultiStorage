#pragma once
#define UNICODE

#include <Windows.h>

template <class DLG>
class DlgBase
{
public:
	static INT_PTR CALLBACK DlgBaseProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void createDialog(const TCHAR * templateName, const HWND & parent);

protected:
	HWND _hDlg;
	INT_PTR CALLBACK DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;
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
	}
	else
		pData = reinterpret_cast<DLG*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	if (pData)
		pData->DlgProc(msg, wParam, lParam);
	else
	{
		MessageBox(NULL, L"Unable to load Dialog Data", L"Error: DlgBaseProc func", MB_OK | MB_ICONERROR);
		return 0;
	}
}

template <class DLG>
void DlgBase<DLG>::createDialog(const TCHAR * templateName, const HWND & parent)
{
	DialogBoxParam(GetModuleHandle(NULL), templateName, parent, DlgBaseProc, this);
}