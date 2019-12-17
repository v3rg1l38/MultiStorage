#pragma once

#include <Windows.h>
#include "../WindowManager/WindowManager.h"

class FrameWindow : public WindowBase<FrameWindow>
{
public:
	~FrameWindow()
	{
		delete this;
	}
	LRESULT CALLBACK MessageHandler(UINT msg, WPARAM wParam, LPARAM lParam);
};