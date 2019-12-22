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
	HWND hWnd = CreateWindow(WC_LISTVIEW, TEXT(""), WS_CHILD | LVS_REPORT | WS_VISIBLE | WS_BORDER,
		xPos,
		yPos,
		xSize,
		ySize,
		parent,
		(HMENU)menu,
		(HINSTANCE)GetModuleHandle(NULL),
		NULL);

	return hWnd;
}

int ListView::insertColumn(const HWND & list,
	const int & colNum,
	const TCHAR * colName,
	const int & colWidth)
{
	LVCOLUMN lCol;
	int columnIndex;

	memset(&lCol, 0, sizeof(lCol));

	lCol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lCol.cx = colWidth;
	lCol.pszText = const_cast<TCHAR*>(colName);
	columnIndex = SendMessage(list, LVM_INSERTCOLUMN, colNum, reinterpret_cast<LPARAM>(&lCol));
	return columnIndex;
}

int ListView::insertItem(const HWND & list, const int & nRow)
{
	LVITEM lItem;
	int itemIndex;

	memset(&lItem, 0, sizeof(lItem));
	lItem.cchTextMax = 512;
	lItem.mask = LVCF_TEXT;

	lItem.iItem = nRow;
	itemIndex = SendMessage(list, LVM_INSERTITEM, 0, reinterpret_cast<LPARAM>(&lItem));
	return itemIndex;
}

void ListView::setItemText(const HWND & list, const TCHAR * value, const int & nRow, const int & nCol)
{
	LVITEM lItem;

	memset(&lItem, 0, sizeof(lItem));
	lItem.cchTextMax = 512;
	lItem.mask = LVCF_TEXT;

	lItem.iItem = nRow;
	lItem.iSubItem = nCol;
	lItem.pszText = const_cast<TCHAR*>(value);
	SendMessage(list, LVM_SETITEMTEXT, nRow, reinterpret_cast<LPARAM>(&lItem));
}

void ListView::setItemInt(const HWND & list, const int & val, const int & nRow, const int & nCol)
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
	SendMessage(list, LVM_SETITEMTEXT, nRow, reinterpret_cast<LPARAM>(&lItem));
}

void ListView::setFullRowSelect(const HWND & list)
{
	SendMessage(list, LVM_SETEXTENDEDLISTVIEWSTYLE,
		LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
}

void ListView::clearList(const HWND & list)
{
	SendMessage(list, LVM_DELETEALLITEMS, 0, 0);
}

const TCHAR * ListView::getDataFromRow(const HWND & list, const int & row, const int & column)
{
	LVITEM lvItem = { 0 };
	TCHAR buff[1024] = TEXT(" ");
	lvItem.mask = LVIF_TEXT;
	lvItem.pszText = buff;
	lvItem.cchTextMax = 1024;
	lvItem.iSubItem = column;
	SendMessage(list, LVM_GETITEMTEXT, row, (LPARAM)&lvItem);
	return lvItem.pszText;
}

int ListView::getDataFromRowInt(const HWND & list, const int & row, const int & column)
{
	LVITEM lvItem = { 0 };
	TCHAR buff[1024] = TEXT(" ");
	lvItem.mask = LVIF_TEXT;
	lvItem.pszText = buff;
	lvItem.cchTextMax = 1024;
	lvItem.iSubItem = column;
	SendMessage(list, LVM_GETITEMTEXT, row, (LPARAM)&lvItem);
	return _wtoi(lvItem.pszText);
}
void ListView::setVisible(const HWND  & list, const int & row)
{
	SendMessage(list, LVM_ENSUREVISIBLE, row, 0);
}

int ListView::findItem(const HWND & list, const TCHAR * code)
{
	LVFINDINFO findInfo;

	findInfo.flags = LVFI_STRING;
	findInfo.psz = code;

	int nIndex = SendMessage(list, LVM_FINDITEM, (WPARAM)-1, (LPARAM)&findInfo);
	return nIndex;
}

int ListView::getSelectedRow(const HWND & list)
{
	int index = SendMessage(list, LVM_GETNEXTITEM, (WPARAM)-1, (LPARAM)LVNI_SELECTED);
	return index;
}

void ListView::setSelectedRow(const HWND & list, const int & row)
{
	LVITEM lvItem;
	lvItem.stateMask = LVIS_SELECTED | LVIS_FOCUSED | LVNI_SELECTED;
	lvItem.state = LVIS_SELECTED | LVIS_FOCUSED | LVNI_SELECTED;
	lvItem.mask = LVIF_STATE;

	SendMessage(list, LVM_SETITEMSTATE, row, reinterpret_cast<LPARAM>(&lvItem));
}

void ListView::unsetSelectedRow(const HWND & list, const int & row)
{
	LVITEM lvItem;
	lvItem.stateMask = LVIS_SELECTED | LVIS_FOCUSED | LVNI_SELECTED;
	lvItem.state = 0;
	lvItem.mask = LVIF_STATE;

	SendMessage(list, LVM_SETITEMSTATE, row, reinterpret_cast<LPARAM>(&lvItem));
}

int ListView::getItemCount(const HWND & list)
{
	int count = SendMessage(list, LVM_GETITEMCOUNT, 0, 0);
	return count;
}

void ListView::setBkColor(const HWND & list, COLORREF col)
{
	SendMessage(list, LVM_SETBKCOLOR, 0, col);
}

void ListView::setTxtBkColor(const HWND  & list, COLORREF col)
{
	SendMessage(list, LVM_SETTEXTBKCOLOR, 0, col);
}