#pragma once

#include <Windows.h>
#include <CommCtrl.h>
#include "../WindowManager/WindowManager.h"
#include "../WindowControls/WindowControls.h"
#include "../ListControls/CList.h"

class FrameWindow : public BaseFrameWindow<FrameWindow>
{
public:
	LRESULT CALLBACK FrameWndProc(UINT msg, WPARAM wParam, LPARAM lParam);
	HWND getClientHandle() const { return _clientArea; }
	virtual void onDestroy();

private:
	bool setClientAreaBackground();
	void initilaizeMenu();
	void onCreate();
	void onChangeSize(LPARAM lParam);
	void commandHandler(WPARAM wParam, LPARAM lParam);
};