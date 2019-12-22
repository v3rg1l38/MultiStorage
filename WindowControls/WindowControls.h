#pragma once

#include <Windows.h>
#include <string>

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
#define ID_CLIENTAREA 9010
#define ID_STORAGE_LIST	9011
#define MENU_FILE 0
#define MENU_INVOICE 1
#define MENU_SETTINGS 2
#define MENU_STORAGE 3

class WindowControls
{
public:
	static void setWindowSize(const HWND & hWnd, const int & sX, const int & sY);
	static std::string getEditText(const HWND & editBox);
	static bool setEditText(const HWND & editBox, const std::string & text);
	static void setSelectedText(const HWND & editBox, const int & start, const int & end);
	static unsigned long getSelectedPos(const HWND & editBox);
	static void replaceSelectedText(const HWND & editBox, const std::string & text, bool undo = true);
};