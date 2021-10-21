#include "BaseWin.h"

void BaseWin::Show(bool _show)
{
	if (_show)
		ShowWindow(hwnd, SW_SHOW);
	else
		ShowWindow(hwnd, SW_HIDE);
}

void BaseWin::Enable(bool _enable)
{
	EnableWindow(hwnd, _enable);
}

void BaseWin::Destroy()
{
	DestroyWindow(hwnd);
}
