#include "CList.h"

HWND CList::createList(HWND parent, 
	const int & xPos, 
	const int & yPos, 
	const int & xSize, 
	const int & ySize,
	const int & menu)
{
	HWND hWnd = CreateWindow(WC_LISTVIEW, "", WS_CHILD | LVS_REPORT | WS_VISIBLE | WS_BORDER,
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

int CList::insertColumn(HWND list, 
	const int & colNum, 
	const char * colName, 
	const int & colWidth)
{
	LVCOLUMN lCol;
	int columnIndex;

	memset(&lCol, 0, sizeof(lCol));

	lCol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lCol.cx = colWidth;
	lCol.pszText = const_cast<LPSTR>(colName);
	columnIndex = SendMessage(list, LVM_INSERTCOLUMN, colNum, reinterpret_cast<LPARAM>(&lCol));
	return columnIndex;
}

int CList::insertItem(HWND list, const int & nRow)
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

void CList::setItemText(HWND list, const char * value, const int & nRow, const int & nCol)
{
	LVITEM lItem;

	memset(&lItem, 0, sizeof(lItem));
	lItem.cchTextMax = 512;
	lItem.mask = LVCF_TEXT;

	lItem.iItem = nRow;
	lItem.iSubItem = nCol;
	lItem.pszText = const_cast<LPSTR>(value);
	SendMessage(list, LVM_SETITEMTEXT, nRow, reinterpret_cast<LPARAM>(&lItem));
}

void CList::setItemInt(HWND list, const int & val, const int & nRow, const int & nCol)
{
	LVITEM lItem;
	char buffer[MAX_PATH] = "";

	memset(&lItem, 0, sizeof(lItem));
	lItem.cchTextMax = 512;
	lItem.mask = LVCF_TEXT;

	lItem.iItem = nRow;
	lItem.iSubItem = nCol;
	sprintf_s(buffer, MAX_PATH, "%d", val);
	lItem.pszText = buffer;
	SendMessage(list, LVM_SETITEMTEXT, nRow, reinterpret_cast<LPARAM>(&lItem));
}

void CList::setFullRowSelect(HWND list)
{
	SendMessage(list, LVM_SETEXTENDEDLISTVIEWSTYLE,
		LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
}

void CList::clearList(HWND list)
{
	SendMessage(list, LVM_DELETEALLITEMS, 0, 0);
}

char * CList::getDataFromRow(HWND list, const int & row, const int & column)
{
	LVITEM lvItem = { 0 };
	char buff[1024] = " ";
	lvItem.mask = LVIF_TEXT;
	lvItem.pszText = buff;
	lvItem.cchTextMax = 1024;
	lvItem.iSubItem = column;
	SendMessage(list, LVM_GETITEMTEXT, row, (LPARAM)&lvItem);
	return lvItem.pszText;
}

int CList::getDataFromRowInt(HWND list, const int & row, const int & column)
{
	LVITEM lvItem = { 0 };
	char buff[1024] = " ";
	lvItem.mask = LVIF_TEXT;
	lvItem.pszText = buff;
	lvItem.cchTextMax = 1024;
	lvItem.iSubItem = column;
	SendMessage(list, LVM_GETITEMTEXT, row, (LPARAM)&lvItem);
	return atoi(lvItem.pszText);
}
void CList::setVisible(HWND list, const int & row)
{
	SendMessage(list, LVM_ENSUREVISIBLE, row, 0);
}

int CList::findItem(HWND list, const char * code)
{
	LVFINDINFO findInfo;

	findInfo.flags = LVFI_STRING;
	findInfo.psz = code;

	int nIndex = SendMessage(list, LVM_FINDITEM, (WPARAM)-1, (LPARAM)&findInfo);
	return nIndex;
}

int CList::getSelectedRow(HWND list)
{
	int index = SendMessage(list, LVM_GETNEXTITEM, (WPARAM)-1, (LPARAM)LVNI_SELECTED);
	return index;
}

void CList::setSelectedRow(HWND list, const int & row)
{
	LVITEM lvItem;
	lvItem.stateMask = LVIS_SELECTED | LVIS_FOCUSED | LVNI_SELECTED;
	lvItem.state = LVIS_SELECTED | LVIS_FOCUSED | LVNI_SELECTED;
	lvItem.mask = LVIF_STATE;

	SendMessage(list, LVM_SETITEMSTATE, row, reinterpret_cast<LPARAM>(&lvItem));
}

void CList::unsetSelectedRow(HWND list, const int & row)
{
	LVITEM lvItem;
	lvItem.stateMask = LVIS_SELECTED | LVIS_FOCUSED | LVNI_SELECTED;
	lvItem.state = 0;
	lvItem.mask = LVIF_STATE;

	SendMessage(list, LVM_SETITEMSTATE, row, reinterpret_cast<LPARAM>(&lvItem));
}

int CList::getItemCount(HWND list)
{
	int count = SendMessage(list, LVM_GETITEMCOUNT, 0, 0);
	return count;
}

void CList::setBkColor(HWND list, COLORREF col)
{
	SendMessage(list, LVM_SETBKCOLOR, 0, col);
}

void CList::setTxtBkColor(HWND list, COLORREF col)
{
	SendMessage(list, LVM_SETTEXTBKCOLOR, 0, col);
}