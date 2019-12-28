#pragma once
#define UNICODE

#include <Windows.h>
#include <vector>
#include "../WindowManager/WindowManager.h"
#include "../WindowControls/WindowControls.h"
#include "../Product/Product.h"

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
	StorageWindow() {}
	LRESULT CALLBACK MDICProc(UINT msg, WPARAM wParam, LPARAM lParam);
	void setProds(std::vector<Product> * prods) { _prods = prods; }

private:
	StorageWindow(const StorageWindow &) = delete;
	StorageWindow & operator=(const StorageWindow &) = delete;

	void onCreate();
	void onResize(LPARAM lParam);
	ListView _listView;
	std::vector<Product> * _prods;
};