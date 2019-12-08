#pragma once

#include <Windows.h>

class WindowControls
{
public:
	static void setWindowSize(const HWND hWnd, const int & sX, const int & sY);
	void initializeMenu(const HWND winHandle);
};