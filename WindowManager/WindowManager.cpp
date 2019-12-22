#include "WindowManager.h"

void MenuControl::DisableMenu(const HWND & window, const int & menuNumber, const int & subMenu)
{
	HMENU hMenu, hSubMenu;
	HWND parent = GetParent(GetParent(window));
	hMenu = GetMenu(parent);

	hSubMenu = GetSubMenu(hMenu, menuNumber);
	EnableMenuItem(hSubMenu, subMenu, MF_BYCOMMAND | MF_GRAYED);
	DrawMenuBar(parent);
}

void MenuControl::EnableMenu(const HWND & window, const int & menuNumber, const int & subMenu)
{
	HMENU hMenu, hSubMenu;
	HWND parent = GetParent(GetParent(window));
	hMenu = GetMenu(parent);

	hSubMenu = GetSubMenu(hMenu, menuNumber);
	EnableMenuItem(hSubMenu, subMenu, MF_BYCOMMAND | MF_ENABLED);
	DrawMenuBar(parent);
}

HWND ListView::createList(const HWND & parent,
	const int & xPos,
	const int & yPos,
	const int & xSize,
	const int & ySize,
	const int & menu)
{
	// Makes sure you can have only one ListView inside each instance of the class
	if (_listHandle)
		return _listHandle;

	HWND hWnd = CreateWindow(WC_LISTVIEW, TEXT(""), WS_CHILD | LVS_REPORT | WS_VISIBLE | WS_BORDER,
		xPos,
		yPos,
		xSize,
		ySize,
		parent,
		(HMENU)menu,
		(HINSTANCE)GetModuleHandle(NULL),
		NULL);

	_listHandle = hWnd;

	return hWnd;
}

int ListView::insertColumn(const int & colNum,
	const TCHAR * colName,
	const int & colWidth)
{
	LVCOLUMN lCol;
	int columnIndex;

	memset(&lCol, 0, sizeof(lCol));

	lCol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lCol.cx = colWidth;
	lCol.pszText = const_cast<TCHAR*>(colName);
	columnIndex = SendMessage(_listHandle, LVM_INSERTCOLUMN, colNum, reinterpret_cast<LPARAM>(&lCol));
	return columnIndex;
}

int ListView::insertItem(const int & nRow)
{
	LVITEM lItem;
	int itemIndex;

	memset(&lItem, 0, sizeof(lItem));
	lItem.cchTextMax = 512;
	lItem.mask = LVCF_TEXT;

	lItem.iItem = nRow;
	itemIndex = SendMessage(_listHandle, LVM_INSERTITEM, 0, reinterpret_cast<LPARAM>(&lItem));
	return itemIndex;
}

void ListView::setItemText(const TCHAR * value, const int & nRow, const int & nCol)
{
	LVITEM lItem;

	memset(&lItem, 0, sizeof(lItem));
	lItem.cchTextMax = 512;
	lItem.mask = LVCF_TEXT;

	lItem.iItem = nRow;
	lItem.iSubItem = nCol;
	lItem.pszText = const_cast<TCHAR*>(value);
	SendMessage(_listHandle, LVM_SETITEMTEXT, nRow, reinterpret_cast<LPARAM>(&lItem));
}

void ListView::setItemInt(const int & val, const int & nRow, const int & nCol)
{
	LVITEM lItem;
	TCHAR buffer[MAX_PATH] = TEXT("");

	memset(&lItem, 0, sizeof(lItem));
	lItem.cchTextMax = 512;
	lItem.mask = LVCF_TEXT;

	lItem.iItem = nRow;
	lItem.iSubItem = nCol;
	_snwprintf_s(buffer, MAX_PATH, TEXT("%d"), val);
	lItem.pszText = buffer;
	SendMessage(_listHandle, LVM_SETITEMTEXT, nRow, reinterpret_cast<LPARAM>(&lItem));
}

void ListView::setFullRowSelect()
{
	SendMessage(_listHandle, LVM_SETEXTENDEDLISTVIEWSTYLE,
		LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
}

void ListView::clearList()
{
	SendMessage(_listHandle, LVM_DELETEALLITEMS, 0, 0);
}

const TCHAR * ListView::getDataFromRow(const int & row, const int & column)
{
	LVITEM lvItem = { 0 };
	TCHAR buff[1024] = TEXT(" ");
	lvItem.mask = LVIF_TEXT;
	lvItem.pszText = buff;
	lvItem.cchTextMax = 1024;
	lvItem.iSubItem = column;
	SendMessage(_listHandle, LVM_GETITEMTEXT, row, reinterpret_cast<LPARAM>(&lvItem));
	return lvItem.pszText;
}

int ListView::getDataFromRowInt(const int & row, const int & column)
{
	LVITEM lvItem = { 0 };
	TCHAR buff[1024] = TEXT(" ");
	lvItem.mask = LVIF_TEXT;
	lvItem.pszText = buff;
	lvItem.cchTextMax = 1024;
	lvItem.iSubItem = column;
	SendMessage(_listHandle, LVM_GETITEMTEXT, row, reinterpret_cast<LPARAM>(&lvItem));
	return _wtoi(lvItem.pszText);
}
void ListView::setVisible(const int & row)
{
	SendMessage(_listHandle, LVM_ENSUREVISIBLE, row, 0);
}

int ListView::findItem(const TCHAR * code)
{
	LVFINDINFO findInfo;

	findInfo.flags = LVFI_STRING;
	findInfo.psz = code;

	int nIndex = SendMessage(_listHandle, LVM_FINDITEM, static_cast<WPARAM>(-1), reinterpret_cast<LPARAM>(&findInfo));
	return nIndex;
}

int ListView::getSelectedRow()
{
	int index = SendMessage(_listHandle, LVM_GETNEXTITEM, static_cast<WPARAM>(-1), static_cast<LPARAM>(LVNI_SELECTED));
	return index;
}

void ListView::setSelectedRow(const int & row)
{
	LVITEM lvItem;
	lvItem.stateMask = LVIS_SELECTED | LVIS_FOCUSED | LVNI_SELECTED;
	lvItem.state = LVIS_SELECTED | LVIS_FOCUSED | LVNI_SELECTED;
	lvItem.mask = LVIF_STATE;

	_oldRowSelected = _rowSelected;
	_rowSelected = row;

	SendMessage(_listHandle, LVM_SETITEMSTATE, row, reinterpret_cast<LPARAM>(&lvItem));
}

void ListView::unsetSelectedRow(const int & row)
{
	LVITEM lvItem;
	lvItem.stateMask = LVIS_SELECTED | LVIS_FOCUSED | LVNI_SELECTED;
	lvItem.state = 0;
	lvItem.mask = LVIF_STATE;

	SendMessage(_listHandle, LVM_SETITEMSTATE, row, reinterpret_cast<LPARAM>(&lvItem));
}

int ListView::getItemCount()
{
	int count = SendMessage(_listHandle, LVM_GETITEMCOUNT, 0, 0);
	return count;
}

void ListView::setBkColor(COLORREF col)
{
	SendMessage(_listHandle, LVM_SETBKCOLOR, 0, col);
}

void ListView::setTxtBkColor(COLORREF col)
{
	SendMessage(_listHandle, LVM_SETTEXTBKCOLOR, 0, col);
}