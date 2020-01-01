#include "SettingsDialog.h"

INT_PTR SettingsDialog::DlgProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(_hDlg, 1);
			break;

		case IDCANCEL:
			EndDialog(_hDlg, 0);
			break;
		}
	}
	default:
		return 0;
	}

	return 0;
}
