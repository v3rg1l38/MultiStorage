//#include "InvoiceWindow.h"
//
//LRESULT CALLBACK InvoiceProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	static int cX, cY;
//	static HWND list;
//
//	switch (msg)
//	{
//	case WM_CREATE:
//	{
//		RECT rc;
//		GetClientRect(hWnd, &rc);
//		list = CList::createList(hWnd,
//			0,
//			0,
//			rc.right - 160,
//			rc.bottom - 150,
//			NULL);
//		CList::setFullRowSelect(list);
//		CList::insertColumn(list,
//			0,
//			"Year",
//			0x54);
//		CList::insertColumn(list,
//			1,
//			"Name",
//			0x124);
//		CList::insertItem(list, 9999);
//		CList::insertItem(list, 9999);
//		CList::setItemText(list, "2018", 0, 0);
//		CList::setItemText(list, "Storage", 0, 1);
//		CList::setItemText(list, "2019", 1, 0);
//		CList::setItemText(list, "Storage", 1, 1);
//	}
//	break;
//
//	case WM_SIZE:
//	{
//		cX = LOWORD(lParam);
//		cY = HIWORD(lParam);
//	}
//	return DefMDIChildProc(hWnd, msg, wParam, lParam);
//
//	default:
//		return DefMDIChildProc(hWnd, msg, wParam, lParam);
//	}
//
//	return 0;
//}