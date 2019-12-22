#pragma once
#define UNICODE

#include <Windows.h>
#include <CommCtrl.h>
#include <map>
#include <string>
#include "../WindowControls/WindowControls.h"
#include <vector>

template<class Window>
class BaseFrameWindow
{
public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void createWindow(const TCHAR * name,
		const int & x = CW_USEDEFAULT,
		const int & y = CW_USEDEFAULT,
		const int & cX = CW_USEDEFAULT,
		const int & cY = CW_USEDEFAULT,
		const HINSTANCE & hInst = GetModuleHandle(NULL),
		const HWND & parent = NULL,
		const long & style = WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		const HMENU & menu = NULL);

	HWND getWindowHandle() const { return _mHwnd; }
	HWND getClientArea() const { return _clientArea; }
protected:
	virtual LRESULT CALLBACK FrameWndProc(UINT msg, WPARAM wParam, LPARAM lParam) = 0;
	HWND _mHwnd; // Frame window Handle
	HWND _clientArea; // MDICLIENT Handle
	HWND _toolbar;
	int _cX;
	int _cY;
};

template<class Window>
LRESULT BaseFrameWindow<Window>::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window * pData = nullptr;

	if (msg == WM_NCCREATE)
	{
		CREATESTRUCT * cStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
		pData = reinterpret_cast<Window*>(cStruct->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pData));

		pData->_mHwnd = hWnd;
	}
	else if (msg == WM_DESTROY)
	{
		DestroyWindow(GetWindow(hWnd, GW_CHILD));
		delete reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(nullptr));
		pData = nullptr;
		PostQuitMessage(0);
	}
	else
	{
		pData = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}

	if (pData)
		return pData->FrameWndProc(msg, wParam, lParam);
	else
		return DefWindowProc(hWnd, msg, wParam, lParam);
}

template<class Window>
void BaseFrameWindow<Window>::createWindow(const TCHAR * name,
	const int & x, 
	const int & y, 
	const int & cX, 
	const int & cY, 
	const HINSTANCE & hInst, 
	const HWND & parent, 
	const long & style, 
	const HMENU & menu)
{
	WNDCLASS wc = {};

	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(LTGRAY_BRUSH));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = TEXT("FrameWindow");
	wc.lpfnWndProc = Window::WndProc;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, TEXT("Unable to register Frame Window class"), TEXT("Error: BaseFrameWindow"), MB_ICONERROR | MB_OK);
		return;
	}

	HWND newFrame = CreateWindowEx(0,
		TEXT("FrameWindow"),
		name,
		style,
		x,
		y,
		cX,
		cY,
		parent,
		menu,
		hInst,
		this);

	if (!newFrame)
	{
		MessageBox(NULL, TEXT("Unable to create Frame Window"), TEXT("Error: BaseFrameWindow"), MB_ICONERROR | MB_OK);
		return;
	}

	_mHwnd = newFrame;
}

template <class MDIChild>
class BaseMDIChild
{
public:
	static LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void createMDIChild(const TCHAR * className,
		const TCHAR * name,
		const HWND & parent = NULL,
		const long & style = WS_OVERLAPPEDWINDOW,
		const int & x = CW_USEDEFAULT,
		const int & y = CW_USEDEFAULT,
		const int & cX = CW_USEDEFAULT,
		const int & cY = CW_USEDEFAULT,
		const HINSTANCE & hInst = GetModuleHandle(NULL),
		const HMENU & menu = NULL);
	bool isReady() const { return _isReady; }
	void setReady() { _isReady = true; }
	HWND getWindowHandle() const { return _mHwnd; }

protected:
	virtual LRESULT CALLBACK MDICProc(UINT msg, WPARAM wParam, LPARAM lParam) = 0;
	HWND _mHwnd; // Window Handle;
	HWND _parentFrame; // Parent Frame Window not the MDICLIENT Window
	int _cX;
	int _cY;
	bool _isReady = false;
};

template<class MDIChild>
inline LRESULT BaseMDIChild<MDIChild>::ChildWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	MDIChild * pData;

	if (msg == WM_NCCREATE)
	{
		CREATESTRUCT * cStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
		MDICREATESTRUCT * mStruct = reinterpret_cast<MDICREATESTRUCT*>(cStruct->lpCreateParams);
		pData = reinterpret_cast<MDIChild*>(mStruct->lParam);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pData));
		pData->_mHwnd = hWnd;
	}
	else if (msg == WM_DESTROY)
	{
		delete reinterpret_cast<MDIChild*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(nullptr));
		pData = nullptr;
	}
	else
	{
		pData = reinterpret_cast<MDIChild*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}
	if (pData)
		return pData->MDICProc(msg, wParam, lParam);
	else
		return DefMDIChildProc(hWnd, msg, wParam, lParam);
}

template<class MDIChild>
inline void BaseMDIChild<MDIChild>::createMDIChild(const TCHAR * className,
	const TCHAR * name,
	const HWND & parent, 
	const long & style, 
	const int & x, 
	const int & y, 
	const int & cX, 
	const int & cY, 
	const HINSTANCE & hInst, 
	const HMENU & menu)
{
	WNDCLASS wc = {};
	if (!GetClassInfo(GetModuleHandle(NULL), className, &wc))
	{
		wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(LTGRAY_BRUSH));
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.style = CS_VREDRAW | CS_HREDRAW;
		wc.hInstance = GetModuleHandle(NULL);
		wc.lpszClassName = className;
		wc.lpfnWndProc = MDIChild::ChildWndProc;

		if (!RegisterClass(&wc))
		{
			MessageBox(NULL, TEXT("Unable to create MDI Child Class"), TEXT("Error"), MB_OK | MB_ICONERROR);
			return;
		}
	}
	
	HWND mdiChild = CreateMDIWindow(className,
		name,
		style,
		x,
		y,
		cX,
		cY,
		parent,
		hInst,
		reinterpret_cast<LPARAM>(this));

	if (!mdiChild)
	{
		MessageBox(NULL, TEXT("Unable to create MDI Child Window"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return;
	}

	_mHwnd = mdiChild;
	_parentFrame = GetParent(parent);

}

class MenuControl 
{
public:
	void DisableMenu(const HWND & window, const int & menuNumber, const int & subMenu);
	void EnableMenu(const HWND & window, const int & menuNumber, const int & subMenu);
};

template <class Window>
Window * getWindowData(const HWND & window)
{
	return reinterpret_cast<Window*>(GetWindowLongPtr(window, GWLP_USERDATA));
}

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
	Button() {}
	HWND createButton(const HWND & parent,
		const TCHAR * name, 
		const int & posX,
		const int & posY,
		const int & sizeX,
		const int & sizeY,
		const HMENU & menu = NULL,
		const long & style = BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD);
	HWND getButton() const { return _buttonHandle; }

private:
	Button(const Button &) = delete;
	Button & operator=(const Button &) = delete;
	HWND _buttonHandle = 0;
};

class Edit
{
public:
	Edit() {}
	HWND createEdit(const HWND & parent,
		const TCHAR * text,
		const int & posX,
		const int & posY,
		const int & sizeX,
		const int & sizeY,
		const HMENU & menu = NULL,
		const long & style = ES_AUTOHSCROLL | WS_BORDER | WS_CHILD | WS_VISIBLE);

private:

	Edit(const Edit &) = delete;
	Edit & operator=(const Edit &) = delete;
	HWND _editHandle = 0;
};