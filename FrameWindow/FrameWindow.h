#pragma once

#include <Windows.h>
#include "../ListControls/CList.h"
#include "../WindowManager/WindowManager.h"
#include "../WindowControls/WindowControls.h"

class FrameWindow : public BaseFrameWindow<FrameWindow>
{
public:
	LRESULT CALLBACK MessageHandler(UINT msg, WPARAM wParam, LPARAM lParam);
private:
	void initilaizeMenu();
	bool setClientAreaBackground();
	int _cX;
	int _cY;
};