#include "WindowManager.h"

std::map<std::string, HWND> WindowManager::_windowsList;

void WindowManager::registerClass(const char * className, 
	HINSTANCE hInstance, 
	LRESULT __stdcall fp(HWND, UINT, WPARAM, LPARAM))
{
	WNDCLASS wc = {};
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = fp;
	wc.lpszClassName = className;
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "Unable to register Window Class", "Error", MB_ICONERROR | MB_OK);
		return;
	}
}

HWND WindowManager::createWindow(const char * name, 
	const char * className, 
	const int & x, 
	const int & y, 
	const int & cX, 
	const int & cY,
	HINSTANCE hInst,
	HWND parent,
	long style,
	HMENU menu)
{
	HWND newWindow = CreateWindow(className,
		name,
		style,
		x,
		y,
		cX,
		cY,
		parent,
		menu,
		hInst,
		NULL);

	if (!newWindow)
	{
		MessageBox(NULL, "Unable to create Window", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	std::string nName = name;
	_windowsList.insert(std::pair<std::string, HWND>(nName, newWindow));

	return newWindow;
}

void WindowManager::addWindowToList(const std::string & winName, const HWND windowHandle)
{
	_windowsList.insert(std::make_pair<std::string, HWND>(static_cast<std::string>(winName), static_cast<HWND>(windowHandle)));
}
