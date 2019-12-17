#pragma once

#include <Windows.h>
#include <CommCtrl.h>
#include "../WindowManager/WindowManager.h"
#include "../WindowControls/WindowControls.h"

class FrameWindow : public WindowBase<FrameWindow>
{
public:
	LRESULT CALLBACK MessageHandler(UINT msg, WPARAM wParam, LPARAM lParam);
	HWND getClientHandle() const { return _clientHwnd; }
private:
	bool setClientAreaBackground();
	void initilaizeMenu();
	void onCreate();
	void onChangeSize(LPARAM lParam);
	void commandHandler(WPARAM wParam, LPARAM lParam);
	HWND _clientHwnd;
	HWND _toolBar;
	int _cX;
	int _cY;
};