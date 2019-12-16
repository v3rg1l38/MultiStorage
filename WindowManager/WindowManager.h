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
		const int & x,
		const int & y,
		const int & cX,
		const int & cY,
		HINSTANCE hInst,
		HWND parent = NULL,
		long style = WS_OVERLAPPEDWINDOW,
		HMENU menu = NULL);
	static HWND createMDIChild(const HWND & clientHandle, 
		const char * title, 
		const char * childClass,
		const int & cX,
		const int & cY);
	static inline HWND getWindowHandle(const std::string & winName) { return _windowsList[winName]; }
	static inline bool destroyWindow(const std::string & winName)
	{
		return DestroyWindow(_windowsList[winName]);
	}
	static void addWindowToList(const std::string & winName, const HWND & windowHandle);

private:
	static std::map<std::string, HWND> _windowsList;
};

template<class DerWind>
class BaseFrameWindow
{
public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		DerWind * ptr = nullptr;

		if (msg == WM_NCCREATE)
		{
			CREATESTRUCT * pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
			ptr = static_cast<DerWind*>(pCreate->lpCreateParams);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(ptr));

			ptr->_hWnd = hWnd;
		}
		else
		{
			ptr = reinterpret_cast<DerWind*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		}

		if (ptr)
		{
			return ptr->MessageHandler(msg, wParam, lParam);
		}
		else
		{
			return DefFrameProc(hWnd, GetDlgItem(hWnd, ID_CLIENTAREA), msg, wParam, lParam);
		}
	}

	bool create(const char * className,
		const char * windowName,
		const long & dwStyle,
		const int & posX,
		const int & posY,
		const int & sizeX,
		const int & sizeY,
		const HINSTANCE & hInst,
		const HWND & parent = 0,
		const HMENU & menu = 0
	)
	{
		WNDCLASS wc = {};

		wc.lpfnWndProc = DerWind::WndProc;
		wc.hInstance = hInst;
		wc.lpszClassName = className;
		wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(LTGRAY_BRUSH));
		wc.style = CS_VREDRAW | CS_HREDRAW;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);

		if (!RegisterClass(&wc))
		{
			MessageBox(NULL, "Unable to register Frame Window Class", "Error: FrameBaseClass", MB_OK | MB_ICONERROR);
			return false;
		}

		_hWnd = CreateWindow(className,
			windowName,
			dwStyle,
			posX,
			posY,
			sizeX,
			sizeY,
			parent,
			menu,
			hInst,
			this);

		return _hWnd ? true : false;
	}

	operator HWND() const { return _hWnd; }

protected:
	virtual LRESULT CALLBACK MessageHandler(UINT msg, WPARAM wParam, LPARAM lParam) = 0;
	HWND _hWnd;
	HWND _clientHwnd;
	HWND _toolBar;
};

template <class MDIChild>
class MDIChildBase
{
public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		MDIChild * ptr = nullptr;

		/*if (msg == WM_NCCREATE)
		{
			CREATESTRUCT * pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
			ptr = static_cast<MDIChild*>(pCreate->lpCreateParams);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(ptr));

			ptr->_hWnd = hWnd;
		}
		else
		{
			ptr = reinterpret_cast<MDIChild*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		}*/
		if (ptr)
		{
			return ptr->MessageHandler(msg, wParam, lParam);
		}
		else
		{
			return DefMDIChildProc(hWnd, msg, wParam, lParam);
		}

	}

	bool create(const char * className,
		const char * windowName,
		const int & posX,
		const int & posY,
		const int & sizeX,
		const int & sizeY,
		const HINSTANCE & hInst,
		const HWND & parent = 0,
		const HMENU & menu = 0
	)
	{
		WNDCLASS wc = {};

		wc.lpfnWndProc = MDIChild::WndProc;
		wc.hInstance = hInst;
		wc.lpszClassName = className;
		wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(LTGRAY_BRUSH));
		wc.style = CS_VREDRAW | CS_HREDRAW;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);

		if (!RegisterClass(&wc))
		{
			MessageBox(NULL, "Unable to register Frame Window Class", "Error: FrameBaseClass", MB_OK | MB_ICONERROR);
			return false;
		}

		_hWnd = CreateWindowEx(WS_EX_MDICHILD,
			className,
			windowName,
			WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE,
			posX,
			posY,
			sizeX,
			sizeY,
			parent,
			menu,
			GetModuleHandle(NULL),
			this);

		return _hWnd ? true : false;
	}

	operator HWND() const { return _hWnd; }

protected:
	virtual LRESULT CALLBACK MessageHandler(UINT msg, WPARAM wParam, LPARAM lParam) = 0;
	HWND _hWnd;

};