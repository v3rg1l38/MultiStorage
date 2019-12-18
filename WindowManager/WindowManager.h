#pragma once

#include <Windows.h>
#include <map>
#include <string>
#include "../WindowControls/WindowControls.h"
#include <vector>

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
	std::vector<HWND> _children;
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
	const HINSTANCE & hInst, 
	const HWND & parent, 
	const long & style, 
	const HMENU & menu)
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

	_mHwnd = newFrame;
}

template <class MDIChild>
class BaseMDIChild
{
public:
	static LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void createMDIChild(const char * className,
		const char * name,
		const HWND & parent = NULL,
		const int & x = CW_USEDEFAULT,
		const int & y = CW_USEDEFAULT,
		const int & cX = CW_USEDEFAULT,
		const int & cY = CW_USEDEFAULT,
		const HINSTANCE & hInst = GetModuleHandle(NULL),
		const long & style = WS_OVERLAPPEDWINDOW,
		const HMENU & menu = NULL);
	bool isReady() const { return _isReady; }
	void setReady() { _isReady = true; }
	HWND getWindowHandle() const { return _mHwnd; }

protected:
	virtual void onCreate() = 0;
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
	MDIChild * pData = reinterpret_cast<MDIChild*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	if (pData)
	{
		if (!pData->isReady())
		{
			pData->setReady();
			pData->onCreate();
		}
		if (msg == WM_DESTROY)
		{
			delete pData;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(nullptr));
			return DefMDIChildProc(hWnd, msg, wParam, lParam);
		}

		return pData->MDICProc(msg, wParam, lParam);
	}
	else
		return DefMDIChildProc(hWnd, msg, wParam, lParam);
}

template<class MDIChild>
inline void BaseMDIChild<MDIChild>::createMDIChild(const char * className, 
	const char * name, 
	const HWND & parent, 
	const int & x, 
	const int & y, 
	const int & cX, 
	const int & cY, 
	const HINSTANCE & hInst, 
	const long & style, 
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
			MessageBox(NULL, "Unable to create MDI Child Class", "Error", MB_OK | MB_ICONERROR);
			return;
		}
	}
	
	HWND mdiChild = CreateWindowEx(WS_EX_MDICHILD,
		className,
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

	if (!mdiChild)
	{
		MessageBox(NULL, "Unable to create MDI Child Window", "Error", MB_OK | MB_ICONERROR);
		return;
	}
	SetWindowLongPtr(mdiChild, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	_mHwnd = mdiChild;
	_parentFrame = GetParent(parent);

}
