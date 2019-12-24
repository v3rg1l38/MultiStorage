#pragma once
#define UNICODE

#include <Windows.h>
#include <CommCtrl.h>
#include <string>

#define MENU_FILE_OPEN 9000
#define MENU_FILE_SAVE 9001
#define MENU_FILE_LOAD 9002
#define MENU_INVOICE_NEW 9003
#define MENU_INVOICE_LOAD 9004
#define MENU_INVOICE_LIST 9005
#define MENU_SETTINGS_GLOBAL 9006
#define MENU_FILE_CLOSE 9007
#define MENU_STORAGE_LIST 9008
#define MENU_STORAGE_EXPORT 9009
#define ID_CLIENTAREA 9010
#define ID_STORAGE_LIST	9011
#define MENU_FILE 0
#define MENU_INVOICE 1
#define MENU_SETTINGS 2
#define MENU_STORAGE 3

class WindowControls
{
public:
	static void setWindowSize(const HWND & hWnd, const int & sX, const int & sY);
	static std::string getEditText(const HWND & editBox);
	static bool setEditText(const HWND & editBox, const std::string & text);
	static void setSelectedText(const HWND & editBox, const int & start, const int & end);
	static unsigned long getSelectedPos(const HWND & editBox);
	static void replaceSelectedText(const HWND & editBox, const std::string & text, bool undo = true);
};

class MenuControl
{
public:
	void DisableMenu(const HWND & window, const int & menuNumber, const int & subMenu);
	void EnableMenu(const HWND & window, const int & menuNumber, const int & subMenu);
};

class ListView
{
public:
	ListView() {}
	HWND createList(const HWND & parent,
		const int & xPos,
		const int & yPos,
		const int & xSize,
		const int & ySize,
		const int & menu);
	int insertColumn(const int & colNum, const TCHAR * colName, const int & colWidth);
	int insertItem(const int & nRow);
	void setItemText(const TCHAR * value, const int & nRow, const int & nCol);
	void setItemInt(const int & val, const int & nRow, const int & nCol);
	void setFullRowSelect();
	void clearList();
	const TCHAR * getDataFromRow(const int & row, const int & column);
	int getDataFromRowInt(const int & row, const int & column);
	void setVisible(const int & row);
	int findItem(const TCHAR * code);
	int getSelectedRow();
	void setSelectedRow(const int & row);
	void unsetSelectedRow(const int & row);
	int getItemCount();
	void setBkColor(COLORREF col);
	void setTxtBkColor(COLORREF col);
	HWND getListHandle() const { return _listHandle; }

private:

	ListView(const ListView &) = delete;
	ListView & operator=(const ListView &) = delete;

	HWND _listHandle = 0;
	int _rowSelected = -1;
	int _oldRowSelected = -1;
};

class Button
{
public:
	Button(const HWND & parent,
		const TCHAR * name,
		const int & posX,
		const int & posY,
		const int & sizeX,
		const int & sizeY,
		const HMENU & menu = NULL,
		const long & style = BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD);

	HWND getButtonHandle() const { return _buttonHandle; }
	int getPosX() const { return _posX; }
	int getPosY() const { return _posY; }
	int getWidth() const { return _width; }
	int getHeight() const { return _height; }

private:
	HWND _buttonHandle;
	int _posX;
	int _posY;
	int _width;
	int _height;
};

class Edit
{
public:
	Edit(const HWND & parent,
		const TCHAR * text,
		const int & posX,
		const int & posY,
		const int & sizeX,
		const int & sizeY,
		const HMENU & menu = NULL,
		const long & style = ES_AUTOHSCROLL | WS_BORDER | WS_CHILD | WS_VISIBLE | WS_TABSTOP);

	HWND getHandle() const { return _editHandle; }
	int getPosX() const { return _posX; }
	int getPosY() const { return _posY; }
	int getWidth() const { return _width; }
	int getHeight() const { return _height; }

private:

	HWND _editHandle;
	int _posX;
	int _posY;
	int _width;
	int _height;
};

class ScrollBar
{
public:

	void setVertScroll(const HWND & window, const int & min, const int & max, const int & pageSize);
	void setHorzScroll(const HWND & window, const int & min, const int & max, const int & pageSize);
	void getVertScrollInfo(const HWND & window);
	void getHorzScrollInfo(const HWND & window);
	void onVertScroll(const HWND & window, WPARAM wParam);
	void onSettingChange(); // WM_SETTINGCHANGE
	void onMouseWheelScroll(const HWND & window, WPARAM wParam);

protected:
	SCROLLINFO _si;
	int _vertPos;
	int _horzPost;
	int _iDeltaPerLine;
	int _iAcumDelta;
	unsigned long _ulScrollLines;
};

class StaticText
{
public:
	StaticText(const HWND & parent,
		const TCHAR * text,
		const int & posX,
		const int & posY,
		const int & sizeX,
		const int & sizeY,
		const HMENU & menu = NULL,
		const long & style = WS_CHILD | WS_VISIBLE);

	HWND getStaticHandle() const { return _staticHandle; }

private:
	StaticText(const StaticText &) = delete;
	StaticText & operator=(const StaticText &) = delete;
	HWND _staticHandle;
};