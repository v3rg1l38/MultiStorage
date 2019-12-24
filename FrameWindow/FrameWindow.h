#pragma once
#define UNICODE

#include <Windows.h>
#include <CommCtrl.h>
#include "../WindowManager/WindowManager.h"

class FrameWindow : public BaseFrameWindow<FrameWindow>
{
public:
	FrameWindow() {}
	LRESULT CALLBACK FrameWndProc(UINT msg, WPARAM wParam, LPARAM lParam);

private:
	FrameWindow(const FrameWindow &) = delete;
	FrameWindow & operator=(const FrameWindow &) = delete;

	void setClientAreaBackground();
	void initilaizeMenu();
	void onCreate();
	void onChangeSize(LPARAM lParam);
	void commandHandler(WPARAM wParam, LPARAM lParam);
};