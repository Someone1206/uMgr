#pragma once
#include "Bits.h"

class BaseWin
{
public:
	HWND hwnd;
	HWND parent;
	Point position;
	Size size;

	// functions are smol so its better to initialise them inline
	// && ignore warnings blabbering abt uninitialized hwnd

	BaseWin() {}

	BaseWin(const Point& pos, const Size& _size, HWND _parent)
		:position(pos), size(_size), parent(_parent)
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

	void EnablePar(bool _enable = true) {
		EnableWindow(parent, _enable);
	}

	void Destroy() {
		DestroyWindow(hwnd);
	}
};

