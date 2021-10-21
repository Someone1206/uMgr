#pragma once
#include <Windows.h>

class Size
{
public:
	int x = 0, y = 0;
	Size(int _x = CW_USEDEFAULT, int _y = CW_USEDEFAULT)
		:x(_x), y(_y)
	{ /* :> */ }

	Size operator+(const Size& size) {
		Size res;
		res.x = x + size.x;
		res.y = y + size.y;
		return res;
	}
	Size operator-(const Size& size) {
		Size res;
		res.x = x - size.x;
		res.y = y - size.y;
		return res;
	}

	~Size() {
		// read manga...
	}
};

