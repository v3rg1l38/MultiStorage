#pragma once

#include <Windows.h>
#include <map>
#include <string>
#include "../WindowControls/WindowControls.h"

class WindowManager
{
public:
	/*
		className - name of the window class
		hInstance - instance
		fp - window proc function
	*/
	static void registerClass(const char * className,
		HINSTANCE hInstance,
		LRESULT __stdcall fp(HWND, UINT, WPARAM, LPARAM)
	);
	static HWND createWindow(const char * name,
		const char * className,
		const int & x = CW_USEDEFAULT,
		const int & y = CW_USEDEFAULT,
		const int & cX = CW_USEDEFAULT,
		const int & cY = CW_USEDEFAULT,
		HINSTANCE hInst = GetModuleHandle(NULL),
		HWND parent = NULL,
		long style = WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		HMENU menu = NULL);
	static HWND createMDIChild(const HWND & clientHandle, 
		const char * title, 
		const char * childClass,
		const int & cX = CW_USEDEFAULT,
		const int & cY = CW_USEDEFAULT);
	static inline HWND getWindowHandle(const std::string & winName) { return _windowsList[winName]; }
	static inline bool destroyWindow(const std::string & winName)
	{
		return DestroyWindow(_windowsList[winName]);
	}
	static void addWindowToList(const std::string & winName, const HWND & windowHandle);

private:
	static std::map<std::string, HWND> _windowsList;
};

template<class Window>
class BaseFrameWindow
{
public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void createWindow(const char * name,
		const int & x = CW_USEDEFAULT,
		const int & y = CW_USEDEFAULT,
		const int & cX = CW_USEDEFAULT,
		const int & cY = CW_USEDEFAULT,
		HINSTANCE hInst = GetModuleHandle(NULL),
		HWND parent = NULL,
		long style = WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		HMENU menu = NULL);

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
void BaseFrameWindow<Window>::createWindow(const char * name, 
	const int & x, 
	const int & y, 
	const int & cX, 
	const int & cY, 
	HINSTANCE hInst, 
	HWND parent, 
	long style, 
	HMENU menu)
{
	WNDCLASS wc = {};

	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(LTGRAY_BRUSH));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = "FrameWindow";
	wc.lpfnWndProc = Window::WndProc;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "Unable to register Frame Window class", "Error: BaseFrameWindow", MB_ICONERROR | MB_OK);
		return;
	}

	HWND newFrame = CreateWindowEx(0,
		"FrameWindow",
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
		MessageBox(NULL, "Unable to create Frame Window", "Error: BaseFrameWindow", MB_ICONERROR | MB_OK);
		return;
	}

	this->_mHwnd = newFrame;
}