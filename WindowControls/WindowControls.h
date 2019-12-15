#pragma once

#include <Windows.h>

#define MENU_FILE_OPEN 9000
#define MENU_FILE_SAVE 9001
#define MENU_FILE_LOAD 9002
#define MENU_INVOICE_NEW 9003
#define MENU_INVOICE_LOAD 9004
#define MENU_INVOICE_LIST 9005
#define MENU_SETTINGS_GLOBAL 9006
#define MENU_FILE_CLOSE 9007
#define MENU_STORAGE_LIST 9008
#define MENU_STORAGE_EXPORT 9009

class WindowControls
{
public:
	static void setWindowSize(const HWND hWnd, const int & sX, const int & sY);
	void initializeMenu(const HWND winHandle);
};