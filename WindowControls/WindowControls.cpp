#include "WindowControls.h"

void WindowControls::setWindowSize(const HWND hWnd, const int & cX, const int & cY)
{
	SetWindowPos(hWnd, NULL, 0, 0, cX, cY, SWP_NOREPOSITION);
}
