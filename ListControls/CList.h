#pragma once

#include <Windows.h>
#include <CommCtrl.h>
#include <string>

class CList
{
public:
	static HWND createList(const HWND & parent, 
		const int & xPos, 
		const int & yPos, 
		const int & xSize, 
		const int & ySize,
		const int & menu);
	static int insertColumn(const HWND & list, const int & colNum, const char * colName, const int & colWidth);
	static int insertItem(const HWND & list, const int & nRow);
	static void setItemText(const HWND  & list, const char * value, const int & nRow, const int & nCol);
	static void setItemInt(const HWND & list, const int & val, const int & nRow, const int & nCol);
	static void setFullRowSelect(const HWND & list);
	static void clearList(const HWND  & list);
	static const char * getDataFromRow(const HWND & list, const int & row, const int & column);
	static int getDataFromRowInt(const HWND & list, const int & row, const int & column);
	static void setVisible(const HWND & list, const int & row);
	static int findItem(const HWND & list, const char * code);
	static int getSelectedRow(const HWND & list);
	static void setSelectedRow(const HWND & list, const int & row);
	static void unsetSelectedRow(const HWND & list, const int & row);
	static int getItemCount(const HWND & list);
	static void setBkColor(const HWND & list, COLORREF col);
	static void setTxtBkColor(const HWND & list, COLORREF col);
};