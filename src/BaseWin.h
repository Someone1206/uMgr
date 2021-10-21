#pragma once
#include "Bits.h"

class BaseWin
{
public:
	HWND hwnd;
	Point position;
	Size size;

	// functions are smol so its better to initialise them inline
	// && ignore warnings blabbering abt uninitialized hwnd

	BaseWin() {}

	BaseWin(const Point& pos, const Size& _size)
		:position(pos), size(_size)
	{ /* heh */ }

	void Show(bool _show = true) {
		if (_show)
			ShowWindow(hwnd, SW_SHOW);
		else
			ShowWindow(hwnd, SW_HIDE);
	}
	void Enable(bool _enable = true) {
		EnableWindow(hwnd, _enable);
	}
	void Destroy() {
		DestroyWindow(hwnd);
	}
};

