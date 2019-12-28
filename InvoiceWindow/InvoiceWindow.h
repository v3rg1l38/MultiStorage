#pragma once
#define UNICODE

#include <Windows.h>
#include <vector>
#include "../WindowManager/WindowManager.h"
#include "../WindowControls/WindowControls.h"
#include "../Product/Product.h"

#define COLUMN_ID_CODE 100
#define COLUMN_ID_NAME 200
#define COLUMN_ID_UNIT 300
#define COLUMN_ID_COUNT 400
#define COLUMN_ID_RETAILPR 500
#define COLUMN_ID_WHOLEPR 600
#define COLUMN_ID_DISCOUNT 700
#define INPUT_CLIENT_OIB 800
#define INPUT_CLIENT_NAME 801
#define INPUT_INVOICE_NUMBER 802
#define INPUT_INVOICE_DATE 803
#define INPUT_INVOICE_PAYMENT 804

class InvoiceWindow : public BaseMDIChild<InvoiceWindow>,
					  public ScrollBar
{
public:
	InvoiceWindow() {}
	virtual LRESULT CALLBACK MDICProc(UINT msg, WPARAM wParam, LPARAM lParam);
	void setProds(std::vector<Product> * prods) { _prods = prods; }

private:
	std::vector<Edit> _editBoxes;
	std::vector<int> _columns;
	std::vector<Product> * _prods;
	HBRUSH _prodBack;
	HBRUSH _cliBack;
	int _tablePos;
	int _rows;
	void onCreate();
	void onPaint();
	void onResize();
	void searchForData(WPARAM wParam, LPARAM lParam);
	void createInputFields();
	InvoiceWindow(const InvoiceWindow &) = delete;
	InvoiceWindow & operator=(const InvoiceWindow &) = delete;
};
