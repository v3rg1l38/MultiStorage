#include "StorageWindow.h"
#include "../MockingData.h"

LRESULT StorageWindow::MDICProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		onCreate();
		break;

	//case WM_NOTIFY:
	//{
	//	switch ((reinterpret_cast<LPNMHDR>(lParam))->code)
	//	{
	//	case NM_CLICK:
	//		CList::getDataFromRow(_listHandle, 0, COUNT_COLUMN);
	//	}
	//	break;
	//}
	//break;

	case WM_CLOSE:
	{
		MenuControl mc;
		mc.EnableMenu(_mHwnd, MENU_STORAGE, MENU_STORAGE_LIST);
		DestroyWindow(_mHwnd);
	}
	return 0;

	case WM_MDIACTIVATE:
	{
		MenuControl mc;
		mc.DisableMenu(_mHwnd, MENU_STORAGE, MENU_STORAGE_LIST);
	}
	break;

	case WM_SIZE:
		onResize(lParam);
		return DefMDIChildProc(_mHwnd, msg, wParam, lParam);

	default:
		return DefMDIChildProc(_mHwnd, msg, wParam, lParam);
	}

	return 0;
}

void StorageWindow::onCreate()
{
	MySql db("192.168.1.96", "vergil", "matija", "3306");
	db.setSqlCommand("SELECT * FROM Products");
	db.setDbName("Storage");
	db.executeQuery();

	RECT rc;
	GetClientRect(_mHwnd, &rc);
	_listView.createList(_mHwnd, 0, 0, rc.right - rc.left, rc.bottom - rc.top, ID_STORAGE_LIST);
	_listView.setTxtBkColor(RGB(179, 248, 255));
	_listView.setBkColor( RGB(179, 248, 255));
	_listView.insertColumn(COLUMN_CODE, TEXT("Code"), 0x80);
	_listView.insertColumn(COLUMN_NAME, TEXT("Name"), 0x120);
	_listView.insertColumn(COLUMN_DESCRIPTION, TEXT("Description"), 0x80);
	_listView.insertColumn(COLUMN_COUNT, TEXT("Count"), 0x80);
	_listView.insertColumn(COLUMN_PACKAGE, TEXT("Package"), 0x80);
	_listView.insertColumn(COLUMN_NEEDED, TEXT("Needed"), 0x80);
	_listView.insertColumn(COLUMN_RETAILPRICE, TEXT("Retail Price"), 0x80);
	_listView.insertColumn(COLUMN_WHOLESALEPRICE, TEXT("Wholesale Price"), 0x80);
	_listView.setFullRowSelect();

	for (size_t i = 0; i < db.getProductList().size(); ++i)
	{
		_listView.insertItem(99999999);
		_listView.setItemText(db.getProductList().at(i).getCCode(), i, COLUMN_CODE);
		_listView.setItemText(db.getProductList().at(i).getCName(), i, COLUMN_NAME);
		_listView.setItemText(db.getProductList().at(i).getCDescription(), i, COLUMN_DESCRIPTION);
		_listView.setItemInt(db.getProductList().at(i).getCount(), i, COLUMN_COUNT);
		_listView.setItemInt(db.getProductList().at(i).getPackage(), i, COLUMN_PACKAGE);
		_listView.setItemInt(db.getProductList().at(i).getNeeded(), i, COLUMN_NEEDED);
		_listView.setItemText(L"0.0", i, COLUMN_RETAILPRICE);
		_listView.setItemText(L"0.0", i, COLUMN_WHOLESALEPRICE);
	}

	//for (size_t i = 0; i < (sizeof(MockData) / sizeof(MockData[0])); ++i)
	//{
	//	_listView.insertItem(9999999);
	//	_listView.setItemText(MockData[i][0], i, COLUMN_CODE);
	//	_listView.setItemText(MockData[i][1], i, COLUMN_NAME);
	//	_listView.setItemText(MockData[i][2], i, COLUMN_DESCRIPTION);
	//	_listView.setItemText(MockData[i][3], i, COLUMN_COUNT);
	//	_listView.setItemText(MockData[i][4], i, COLUMN_PACKAGE);
	//	_listView.setItemText(MockData[i][5], i, COLUMN_NEEDED);
	//	_listView.setItemText(MockData[i][6], i, COLUMN_RETAILPRICE);
	//	_listView.setItemText(MockData[i][7], i, COLUMN_WHOLESALEPRICE);
	//}

}


void StorageWindow::onResize(LPARAM lParam)
{
	_cX = LOWORD(lParam);
	_cY = HIWORD(lParam);
	WindowControls::setWindowSize(_listView.getListHandle(), _cX, _cY);
}
