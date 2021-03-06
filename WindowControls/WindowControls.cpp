#include "WindowControls.h"

void WindowControls::setWindowSize(const HWND & hWnd, const int & cX, const int & cY)
{
	SetWindowPos(hWnd, NULL, 0, 0, cX, cY, SWP_NOREPOSITION);
}

std::wstring WindowControls::getEditText(const HWND & editBox)
{
	const int textLength = SendMessage(editBox, WM_GETTEXTLENGTH, 0, 0);
	TCHAR * buffer = new TCHAR[textLength + 1];
	SendMessage(editBox,
		WM_GETTEXT,
		static_cast<WPARAM>(textLength + 1),
		reinterpret_cast<LPARAM>(buffer));

	const std::wstring rText = buffer;
	delete[] buffer;
	return rText;
}

bool WindowControls::setEditText(const HWND & editBox, const std::wstring & text)
{
	return SendMessage(editBox, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(text.c_str()));
}

bool WindowControls::setEditText(const HWND & editBox, const TCHAR * text)
{
	return SendMessage(editBox, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(text));
}

void WindowControls::setSelectedText(const HWND & editBox, const int & start, const int & end)
{
	SendMessage(editBox, EM_SETSEL, start, end);
}

// LOWORD -> First char | HIWORD -> one char after last char selected
unsigned long WindowControls::getSelectedPos(const HWND & editBox)
{
	return SendMessage(editBox, EM_GETSEL, 0, 0);
}

void WindowControls::replaceSelectedText(const HWND & editBox, const std::wstring & text, bool undo)
{
	SendMessage(editBox, EM_REPLACESEL, undo, reinterpret_cast<LPARAM>(text.c_str()));
}

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
	const int & colWidth) noexcept
{
	LVCOLUMN lCol;

	memset(&lCol, 0, sizeof(lCol));

	lCol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lCol.cx = colWidth;
	lCol.pszText = const_cast<TCHAR*>(colName);
	return SendMessage(_listHandle, LVM_INSERTCOLUMN, colNum, reinterpret_cast<LPARAM>(&lCol));
}

int ListView::insertItem(const int & nRow) noexcept
{
	LVITEM lItem;

	memset(&lItem, 0, sizeof(lItem));
	lItem.cchTextMax = 512;
	lItem.mask = LVCF_TEXT;

	lItem.iItem = nRow;
	return SendMessage(_listHandle, LVM_INSERTITEM, 0, reinterpret_cast<LPARAM>(&lItem));
}

void ListView::setItemText(const TCHAR * value, const int & nRow, const int & nCol) noexcept
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

void ListView::setItemInt(const int & val, const int & nRow, const int & nCol) noexcept
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

void ListView::setItemDouble(const double & value, const int & nRow, const int & nCol) noexcept
{
	LVITEM lItem;
	TCHAR buffer[MAX_PATH] = TEXT("");

	memset(&lItem, 0, sizeof(lItem));
	lItem.cchTextMax = 512;
	lItem.mask = LVCF_TEXT;

	lItem.iItem = nRow;
	lItem.iSubItem = nCol;

	_snwprintf_s(buffer, MAX_PATH, TEXT("%.2f"), value);
	lItem.pszText = buffer;
	SendMessage(_listHandle, LVM_SETITEMTEXT, nRow, reinterpret_cast<LPARAM>(&lItem));
}

void ListView::setFullRowSelect() noexcept
{
	SendMessage(_listHandle, LVM_SETEXTENDEDLISTVIEWSTYLE,
		LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
}

void ListView::clearList() noexcept
{
	SendMessage(_listHandle, LVM_DELETEALLITEMS, 0, 0);
}

const TCHAR * ListView::getDataFromRow(const int & row, const int & column) noexcept
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

int ListView::getDataFromRowInt(const int & row, const int & column) noexcept
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
void ListView::setVisible(const int & row) noexcept
{
	SendMessage(_listHandle, LVM_ENSUREVISIBLE, row, 0);
}

int ListView::findItem(const TCHAR * code) noexcept
{
	LVFINDINFO findInfo;

	findInfo.flags = LVFI_STRING;
	findInfo.psz = code;

	return SendMessage(_listHandle, LVM_FINDITEM, static_cast<WPARAM>(-1), reinterpret_cast<LPARAM>(&findInfo));
}

int ListView::getSelectedRow() noexcept
{
	return SendMessage(_listHandle, LVM_GETNEXTITEM, static_cast<WPARAM>(-1), static_cast<LPARAM>(LVNI_SELECTED));
}

void ListView::setSelectedRow(const int & row) noexcept
{
	LVITEM lvItem;
	lvItem.stateMask = LVIS_SELECTED | LVIS_FOCUSED | LVNI_SELECTED;
	lvItem.state = LVIS_SELECTED | LVIS_FOCUSED | LVNI_SELECTED;
	lvItem.mask = LVIF_STATE;

	_oldRowSelected = _rowSelected;
	_rowSelected = row;

	SendMessage(_listHandle, LVM_SETITEMSTATE, row, reinterpret_cast<LPARAM>(&lvItem));
}

void ListView::unsetSelectedRow(const int & row) noexcept
{
	LVITEM lvItem;
	lvItem.stateMask = LVIS_SELECTED | LVIS_FOCUSED | LVNI_SELECTED;
	lvItem.state = 0;
	lvItem.mask = LVIF_STATE;

	SendMessage(_listHandle, LVM_SETITEMSTATE, row, reinterpret_cast<LPARAM>(&lvItem));
}

int ListView::getItemCount() noexcept
{
	return SendMessage(_listHandle, LVM_GETITEMCOUNT, 0, 0);
}

void ListView::setBkColor(COLORREF col) noexcept
{
	SendMessage(_listHandle, LVM_SETBKCOLOR, 0, col);
}

void ListView::setTxtBkColor(COLORREF col) noexcept
{
	SendMessage(_listHandle, LVM_SETTEXTBKCOLOR, 0, col);
}

Edit::Edit(const HWND & parent,
	const TCHAR * text,
	const int & posX,
	const int & posY,
	const int & sizeX,
	const int & sizeY,
	const HMENU & menu,
	const long & style)
{
	HWND edit = CreateWindowEx(0,
		TEXT("EDIT"),
		text,
		style,
		posX,
		posY,
		sizeX,
		sizeY,
		parent,
		menu,
		GetModuleHandle(NULL),
		NULL);

	_editHandle = edit;
	_posX = posX;
	_posY = posY;
	_width = sizeX;
	_height = sizeY;
}

inline int Edit::getLength() const noexcept
{
	return SendMessage(_editHandle, WM_GETTEXTLENGTH, 0, 0);
}

void Edit::setData(const TCHAR * data)
{
	_data = data;
	SendMessage(_editHandle, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(data));
}

void Edit::setData(const int & data)
{
	TCHAR buffer[1024] = L"";
	_snwprintf_s(buffer, 1024, L"%d", data);
	SendMessage(_editHandle, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(buffer));
}

void Edit::setData(const double & data)
{
	TCHAR buffer[1024] = L"";
	_snwprintf_s(buffer, 1024, L"%.2f", data);
	SendMessage(_editHandle, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(buffer));
}

void Edit::operator=(const TCHAR * data)
{
	_data = data;
	SendMessage(_editHandle, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(data));
}

void Edit::operator=(const int & data)
{
	TCHAR buffer[1024] = L"";
	_snwprintf_s(buffer, 1024, L"%d", data);
	SendMessage(_editHandle, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(buffer));
}

void Edit::operator=(const double & data)
{
	TCHAR buffer[1024] = L"";
	_snwprintf_s(buffer, 1024, L"%.2f", data);
	SendMessage(_editHandle, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(buffer));
}

const std::wstring Edit::getDataText()
{
	const int length = GetWindowTextLength(_editHandle);
	TCHAR * buffer = new TCHAR[length + 1];
	GetWindowText(_editHandle, buffer, length + 1);
	_data = buffer;
	delete[] buffer;
	return _data;
}

const int Edit::getDataInt()
{
	const int length = GetWindowTextLength(_editHandle);
	TCHAR * buffer = new TCHAR[length + 1];
	GetWindowText(_editHandle, buffer, length + 1);
	_data = buffer;
	const int retVal = _wtoi(buffer);
	delete[] buffer;
	return retVal;
}

const double Edit::getDataDouble()
{
	const int length = GetWindowTextLength(_editHandle);
	TCHAR * buffer = new TCHAR[length + 1];
	GetWindowText(_editHandle, buffer, length + 1);
	_data = buffer;
	const double retVal = _wtof(buffer);
	delete[] buffer;
	return retVal;
}

Edit::operator const TCHAR*()
{
	getDataText();
	return _data.c_str();
}

void ScrollBar::setVertScroll(const HWND & window, const int & min, const int & max, const int & pageSize) noexcept
{
	_si.cbSize = sizeof(SCROLLINFO);
	_si.fMask = SIF_RANGE | SIF_PAGE;
	_si.nMin = min;
	_si.nMax = max;
	_si.nPage = pageSize;

	SetScrollInfo(window, SB_VERT, &_si, true);
}

void ScrollBar::setHorzScroll(const HWND & window, const int & min, const int & max, const int & pageSize) noexcept
{
	_si.cbSize = sizeof(SCROLLINFO);
	_si.fMask = SIF_RANGE | SIF_PAGE;
	_si.nMin = min;
	_si.nMax = max;
	_si.nPage = pageSize;

	SetScrollInfo(window, SB_HORZ, &_si, true);
}

void ScrollBar::getVertScrollInfo(const HWND & window) noexcept
{
	_si.cbSize = sizeof(SCROLLBARINFO);
	_si.fMask = SIF_ALL;
	GetScrollInfo(window, SB_VERT, &_si);
}

void ScrollBar::getHorzScrollInfo(const HWND & window) noexcept
{
	_si.cbSize = sizeof(SCROLLBARINFO);
	_si.fMask = SIF_ALL;
	GetScrollInfo(window, SB_HORZ, &_si);
}

void ScrollBar::onVertScroll(const HWND & window, WPARAM wParam, const int & charHeight) noexcept
{
	if (!_scrollable)
		return;

	getVertScrollInfo(window);
	_vertPos = _si.nPos;

	switch (LOWORD(wParam))
	{
	case SB_TOP:
		_si.nPos = _si.nMin;
		break;

	case SB_BOTTOM:
		_si.nPos = _si.nMax;
		break;

	case SB_LINEUP:
		_si.nPos -= 1;
		break;

	case SB_LINEDOWN:
		_si.nPos += 1;
		break;

	case SB_PAGEUP:
		_si.nPos -= _si.nPage;
		break;

	case SB_PAGEDOWN:
		_si.nPos += _si.nPage;
		break;

	case SB_THUMBTRACK:
		_si.nPos = _si.nTrackPos;
		break;

	default:
		break;
	}

	_si.fMask = SIF_POS;
	SetScrollInfo(window, SB_VERT, &_si, true);
	GetScrollInfo(window, SB_VERT, &_si);

	if (_si.nPos != _vertPos)
	{
		ScrollWindow(window, 0, charHeight * (_vertPos - _si.nPos), NULL, NULL);
		_vertPos = _si.nPos;
		UpdateWindow(window);
	}
}

void ScrollBar::onSettingChange() noexcept
{
	SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &_ulScrollLines, 0);
	if (_ulScrollLines)
		_iDeltaPerLine = WHEEL_DELTA / _ulScrollLines;
	else
		_iDeltaPerLine = 0;
}

void ScrollBar::onMouseWheelScroll(const HWND & window, WPARAM wParam) noexcept
{
	if (!_scrollable)
		return;

	if (_iDeltaPerLine == 0)
		return;

	_iAcumDelta += static_cast<short>(HIWORD(wParam));

	while (_iAcumDelta >= _iDeltaPerLine)
	{
		SendMessage(window, WM_VSCROLL, SB_LINEUP, 0);
		_iAcumDelta -= _iDeltaPerLine;
	}
	while (_iAcumDelta <= -_iDeltaPerLine)
	{
		SendMessage(window, WM_VSCROLL, SB_LINEDOWN, 0);
		_iAcumDelta += _iDeltaPerLine;
	}
}

Button::Button(const HWND & parent,
	const TCHAR * name,
	const int & posX,
	const int & posY,
	const int & sizeX,
	const int & sizeY,
	const HMENU & menu,
	const long & style)
{
	HWND button = CreateWindowEx(0,
		TEXT("BUTTON"),
		name,
		style,
		posX,
		posY,
		sizeX,
		sizeY,
		parent,
		menu,
		GetModuleHandle(NULL),
		NULL);

	_buttonHandle = button;
	_posX = posX;
	_posY = posY;
	_width = sizeX;
	_height = sizeY;
}

StaticText::StaticText(const HWND & parent,
	const TCHAR * text,
	const int & posX,
	const int & posY,
	const int & sizeX,
	const int & sizeY,
	const HMENU & menu,
	const long & style)
{
	HWND staticText = CreateWindowEx(0,
		TEXT("STATIC"),
		text,
		style,
		posX,
		posY,
		sizeX,
		sizeY,
		parent,
		menu,
		GetModuleHandle(NULL),
		NULL);

	_staticHandle = staticText;
}
