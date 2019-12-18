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
	HWND newWindow = CreateWindowEx(0,
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
		NULL);

	if (!newWindow)
	{
		MessageBox(NULL, "Unable to create Window", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	return newWindow;
}

HWND WindowManager::createMDIChild(const HWND & clientHandle, 
	const char * title, 
	const char * childClass,
	const int & cX,
	const int & cY)
{
	MDICREATESTRUCT mcs;
	HWND mdiChild;

	mcs.szTitle = title;
	mcs.szClass = childClass;
	mcs.hOwner = GetModuleHandle(NULL);
	mcs.x = 0;
	mcs.y = 0;
	mcs.cx = cX;
	mcs.cy = cY;
	mcs.style = MDIS_ALLCHILDSTYLES;

	mdiChild = reinterpret_cast<HWND>(SendMessage(clientHandle, WM_MDICREATE, 0, reinterpret_cast<long>(&mcs)));

	if (!mdiChild)
	{
		MessageBox(NULL, "Unable to create MDI child", "Error", MB_OK);
		return NULL;
	}

	return mdiChild;
}

void WindowManager::addWindowToList(const std::string & winName, const HWND & windowHandle)
{
	_windowsList.insert(std::make_pair<std::string, HWND>(static_cast<std::string>(winName), static_cast<HWND>(windowHandle)));
}


