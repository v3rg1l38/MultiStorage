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

template <class BaseWindow>
class WindowBase
{
public:
	static BaseWindow * getInstance();
	static void removeInstance();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	HWND getHandle() const { return _mHwnd; }
private:

	WindowBase(const WindowBase &) = delete;
	WindowBase & operator=(const WindowBase &) = delete;

	static BaseWindow * _instance;
protected:
	WindowBase() {}
	~WindowBase() 
	{ 
		_instance = nullptr;
	}
	virtual LRESULT CALLBACK MessageHandler(UINT msg, WPARAM wParam, LPARAM lParam) = 0;
	HWND _mHwnd;
};

template<class BaseWindow>
inline BaseWindow * WindowBase<BaseWindow>::getInstance()
{
	if (!_instance)
		_instance = new BaseWindow();

	return _instance;
}

template<class BaseWindow>
inline void WindowBase<BaseWindow>::removeInstance()
{
	_instance = nullptr;
}

template<class BaseWindow>
inline LRESULT WindowBase<BaseWindow>::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	BaseWindow * pThis = BaseWindow::getInstance();

	//if (msg == WM_DESTROY)
	//{
	//	if (pThis)
	//	{
	//		delete pThis;
	//		PostQuitMessage(0);
	//		return 0;
	//	}
	//	else
	//	{
	//		PostQuitMessage(0);
	//		return 0;
	//	}

	//}

	if (pThis)
	{
		pThis->_mHwnd = hWnd;
		return pThis->MessageHandler(msg, wParam, lParam);
	}
	else
		return DefWindowProc(hWnd, msg, wParam, lParam);
}

template<typename T> T*
WindowBase<T>::_instance = nullptr;
