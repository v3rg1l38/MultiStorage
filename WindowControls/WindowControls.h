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
	static std::wstring getEditText(const HWND & editBox);
	static bool setEditText(const HWND & editBox, const std::wstring & text);
	static bool setEditText(const HWND & editBox, const TCHAR * text);
	static void setSelectedText(const HWND & editBox, const int & start, const int & end);
	static unsigned long getSelectedPos(const HWND & editBox);
	static void replaceSelectedText(const HWND & editBox, const std::wstring & text, bool undo = true);
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
	int insertColumn(const int & colNum, const TCHAR * colName, const int & colWidth) noexcept;
	int insertItem(const int & nRow) noexcept;
	void setItemText(const TCHAR * value, const int & nRow, const int & nCol) noexcept;
	void setItemInt(const int & val, const int & nRow, const int & nCol) noexcept;
	void setItemDouble(const double & value, const int & nRow, const int & nCol) noexcept;
	void setFullRowSelect() noexcept;
	inline void clearList() noexcept;
	const TCHAR * getDataFromRow(const int & row, const int & column) noexcept;
	int getDataFromRowInt(const int & row, const int & column) noexcept;
	void setVisible(const int & row) noexcept;
	int findItem(const TCHAR * code) noexcept;
	int getSelectedRow() noexcept;
	inline void setSelectedRow(const int & row) noexcept;
	inline void unsetSelectedRow(const int & row) noexcept;
	inline int getItemCount() noexcept;
	void setBkColor(COLORREF col) noexcept;
	void setTxtBkColor(COLORREF col) noexcept;
	inline HWND getListHandle() const noexcept { return _listHandle; }

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

	inline HWND getButtonHandle() const noexcept { return _buttonHandle; }
	inline int getPosX() const noexcept { return _posX; }
	inline int getPosY() const noexcept { return _posY; }
	inline int getWidth() const noexcept { return _width; }
	inline int getHeight() const noexcept { return _height; }

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

	inline HWND getHandle() const noexcept { return _editHandle; }
	inline int getPosX() const noexcept { return _posX; }
	inline int getPosY() const noexcept { return _posY; }
	inline int getWidth() const noexcept { return _width; }
	inline int getHeight() const noexcept { return _height; }

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
	void setVertScroll(const HWND & window, const int & min, const int & max, const int & pageSize) noexcept;
	void setHorzScroll(const HWND & window, const int & min, const int & max, const int & pageSize) noexcept;
	void getVertScrollInfo(const HWND & window) noexcept;
	void getHorzScrollInfo(const HWND & window) noexcept;
	void onVertScroll(const HWND & window, WPARAM wParam, const int & charHeight) noexcept;
	void onSettingChange() noexcept; // WM_SETTINGCHANGE
	void onMouseWheelScroll(const HWND & window, WPARAM wParam) noexcept;

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

	inline HWND getStaticHandle() const noexcept { return _staticHandle; }

private:
	StaticText(const StaticText &) = delete;
	StaticText & operator=(const StaticText &) = delete;
	HWND _staticHandle;
};