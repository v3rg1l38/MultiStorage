#pragma once
#define UNICODE

#include <Windows.h>
#include "../WindowManager/WindowManager.h"
#include <mysql/jdbc.h>
#define COLUMN_ID_CODE 100
#define COLUMN_ID_NAME 200
#define COLUMN_ID_COUNT 300
#define COLUMN_ID_RETAILPR 400
#define COLUMN_ID_WHOLEPR 500
#define COLUMN_ID_UNIT 600
#define COLUMN_ID_DISCOUNT 700
#define INPUT_CLIENT_OIB 800
#define INPUT_CLIENT_NAME 801
#define INPUT_INVOICE_NUMBER 802
#define INPUT_INVOICE_DATE 803

class InvoiceWindow : public BaseMDIChild<InvoiceWindow>,
					  public ScrollBar
{
public:
	InvoiceWindow() {}
	virtual LRESULT CALLBACK MDICProc(UINT msg, WPARAM wParam, LPARAM lParam);

private:
	std::vector<Edit> _editBoxes;
	std::vector<int> _columns;
	HBRUSH _prodBack;
	HBRUSH _cliBack;
	int _startTablePos;
	int _tablePos;
	void onCreate();
	void onPaint();
	void onResize();
	void createInputFields();
	InvoiceWindow(const InvoiceWindow &) = delete;
	InvoiceWindow & operator=(const InvoiceWindow &) = delete;
};
