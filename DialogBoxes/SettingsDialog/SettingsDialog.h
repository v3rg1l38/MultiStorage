#pragma once
#define UNICODE

#include "../../DlgManager/DlgBase.h"

class SettingsDialog : public DlgBase<SettingsDialog>
{
public:
	INT_PTR CALLBACK DlgProc(UINT msg, WPARAM wParam, LPARAM lParam);
};