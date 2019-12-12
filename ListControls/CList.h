#pragma once

#include <Windows.h>
#include <CommCtrl.h>
#include <string>

class CList
{
public:
	static HWND createList(HWND & parent, 
		const int & xPos, 
		const int & yPos, 
		const int & xSize, 
		const int & ySize,
		const int & menu);
	static int insertColumn(HWND & list, const int & colNum, const char * colName, const int & colWidth);
	static int insertItem(HWND & list, const int & nRow);
	static void setItemText(HWND  & list, const char * value, const int & nRow, const int & nCol);
	static void setItemInt(HWND & list, const int & val, const int & nRow, const int & nCol);
	static void setFullRowSelect(HWND & list);
	static void clearList(HWND  & list);
	static const char * getDataFromRow(HWND & list, const int & row, const int & column);
	static int getDataFromRowInt(HWND & list, const int & row, const int & column);
	static void setVisible(HWND & list, const int & row);
	static int findItem(HWND & list, const char * code);
	static int getSelectedRow(HWND & list);
	static void setSelectedRow(HWND & list, const int & row);
	static void unsetSelectedRow(HWND & list, const int & row);
	static int getItemCount(HWND & list);
	static void setBkColor(HWND & list, COLORREF col);
	static void setTxtBkColor(HWND & list, COLORREF col);
};