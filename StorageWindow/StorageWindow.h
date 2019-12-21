#pragma once
#define UNICODE

#include <Windows.h>
#include "../ListControls/CList.h"
#include "../WindowManager/WindowManager.h"

#define COLUMN_CODE 0
#define COLUMN_NAME 1
#define COLUMN_DESCRIPTION 2
#define COLUMN_COUNT 3
#define COLUMN_PACKAGE 4
#define COLUMN_NEEDED 5
#define COLUMN_RETAILPRICE 6
#define COLUMN_WHOLESALEPRICE 7

class StorageWindow : public BaseMDIChild<StorageWindow>
{
public:
	LRESULT CALLBACK MDICProc(UINT msg, WPARAM wParam, LPARAM lParam);
	HWND getListHandle() const { return _listHandle; }

private:
	void onCreate();
	void onResize(LPARAM lParam);
	HWND _listHandle;
};