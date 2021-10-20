#pragma once
#include <Windows.h>

class Size
{
public:
	int x = 0, y = 0;
	Size(int _x = CW_USEDEFAULT, int _y = CW_USEDEFAULT);

	Size operator+(const Size& size);
	Size operator-(const Size& size);

	~Size();
};

inline Size::Size(int _x, int _y)
{
	x = _x;
	x = _y;
}

inline Size Size::operator+(const Size& size)
{
	Size res;
	res.x = x + size.x;
	res.y = y + size.y;
	return res;
}

inline Size Size::operator-(const Size& size)
{
	Size res;
	res.x = x - size.x;
	res.y = y - size.y;
	return res;
}

inline Size::~Size()
{
	// read some manga.
}

