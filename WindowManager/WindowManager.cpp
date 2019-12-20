#include "WindowManager.h"

std::map<std::string, HWND> WindowManager::_windowsList;


void WindowManager::registerClass(const TCHAR * className,
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
		MessageBox(NULL, TEXT("Unable to register Window Class"), TEXT("Error"), MB_ICONERROR | MB_OK);
		return;
	}
}

HWND WindowManager::createWindow(const TCHAR * name,
	const TCHAR * className,
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
		MessageBox(NULL, TEXT("Unable to create Window"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return 0;
	}

	return newWindow;
}

HWND WindowManager::createMDIChild(const HWND & clientHandle, 
	const TCHAR * title,
	const TCHAR * childClass,
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
		MessageBox(NULL, TEXT("Unable to create MDI child"), TEXT("Error"), MB_OK);
		return NULL;
	}

	return mdiChild;
}

void WindowManager::addWindowToList(const std::string & winName, const HWND & windowHandle)
{
	_windowsList.insert(std::make_pair<std::string, HWND>(static_cast<std::string>(winName), static_cast<HWND>(windowHandle)));
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
