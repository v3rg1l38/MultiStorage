#include <Windows.h>
#include <CommCtrl.h>
#include "WindowManager/WindowManager.h"
#include "FrameWindow/FrameWindow.h"

#pragma comment(lib, "comctl32.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR czCommand, int nShowWindow)
{
	FrameWindow * newWindow = new FrameWindow();
	newWindow->createWindow("Proba");

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if(!TranslateMDISysAccel(newWindow->getClientArea(), &msg))
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	delete newWindow;

	return static_cast<int>(msg.wParam);
}