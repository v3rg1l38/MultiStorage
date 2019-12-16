#pragma once

#include <Windows.h>
#include "../ListControls/CList.h"
#include "../WindowManager/WindowManager.h"
#include "../WindowControls/WindowControls.h"
#include "../FrameWindow/FrameWindow.h"

#define CODE_COLUMN 0
#define NAME_COLUMN 1
#define DESCR_COLUMN 2
#define COUNT_COLUMN 3
#define PACKAGE_COLUMN 4
#define NEEDED_COLUMN 5
#define RETAILPRICE_COLUMN 6
#define WHOLESALE_COLUMN 7

class StorageWindow : public MDIChildBase<StorageWindow>
{
public:
	LRESULT CALLBACK MessageHandler(UINT msg, WPARAM wParam, LPARAM lParam);
	void initilaizeWindow();

private:
	HWND _list;
};