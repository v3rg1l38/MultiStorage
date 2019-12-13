#pragma once

#include <Windows.h>
#include <map>
#include <string>

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
	static HWND createMDIChild(HWND & clientHandle, 
		const char * title, 
		const char * childClass,
		const int & cX,
		const int & cY);
	static inline HWND getWindowHandle(const std::string & winName) { return _windowsList[winName]; }
	static inline bool destroyWindow(const std::string & winName)
	{
		return DestroyWindow(_windowsList[winName]);
	}
	static void addWindowToList(const std::string & winName, const HWND windowHandle);

private:
	static std::map<std::string, HWND> _windowsList;
};