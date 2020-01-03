#pragma once
#define UNICODE

#include <Windows.h>
#include <CommCtrl.h>
#include <vector>
#include "../WindowManager/WindowManager.h"
#include "../Database/Database.h"
#include "../Product/Product.h"
#include "../AppData/AppData.h"

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
	std::vector<Product> _products;
};