#include "WindowControls.h"

void WindowControls::setWindowSize(const HWND & hWnd, const int & cX, const int & cY)
{
	SetWindowPos(hWnd, NULL, 0, 0, cX, cY, SWP_NOREPOSITION);
}

std::string WindowControls::getEditText(const HWND & editBox)
{
	const int textLength = SendMessage(editBox, WM_GETTEXTLENGTH, 0, 0);
	char * buffer = static_cast<char*>(malloc((textLength + 1) * sizeof(char)));
	SendMessage(editBox,
		WM_GETTEXT,
		static_cast<WPARAM>(textLength + 1),
		reinterpret_cast<LPARAM>(buffer));

	const std::string rText = buffer;
	free(buffer);
	return rText;
}

bool WindowControls::setEditText(const HWND & editBox, const std::string & text)
{
	return SendMessage(editBox, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(text.c_str()));
}

void WindowControls::setSelectedText(const HWND & editBox, const int & start, const int & end)
{
	SendMessage(editBox, EM_SETSEL, start, end);
}

// LOWORD -> First char | HIWORD -> one char after last char selected
unsigned long WindowControls::getSelectedPos(const HWND & editBox)
{
	return SendMessage(editBox, EM_GETSEL, 0, 0);
}

void WindowControls::replaceSelectedText(const HWND & editBox, const std::string & text, bool undo)
{
	SendMessage(editBox, EM_REPLACESEL, undo, reinterpret_cast<LPARAM>(text.c_str()));
}
