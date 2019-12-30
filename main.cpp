#define UNICODE

#include <Windows.h>
#include "FrameWindow/FrameWindow.h"

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "UxTheme.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR czCommand, int nShowWindow)
{
	FrameWindow * frameWindow = new FrameWindow();
	frameWindow->createWindow(TEXT("Proba"));
	ShowWindow(*frameWindow, SW_MAXIMIZE);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if (!TranslateMDISysAccel(frameWindow->getClientArea(), &msg))
		{
			if (!IsDialogMessage(GetWindow(frameWindow->getClientArea(), GW_CHILD), &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

	return static_cast<int>(msg.wParam);
}