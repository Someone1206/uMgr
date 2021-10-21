#pragma once
#include <Windows.h>

class Point
{
public:
	int x = 0, y = 0;
	
	Point(int _x = CW_USEDEFAULT, int _y = CW_USEDEFAULT)
		:x(_x), y(_y)
	{ /* :P */ }

	Point operator+(const Point& pt) {
		Point res;
		res.x = x + pt.x;
		res.y = y + pt.y;
		return res;
	}
	Point operator-(const Point& pt) {
		Point res;
		res.x = x - pt.x;
		res.y = y - pt.y;
		return res;
	}

	~Point() {
		/* watch anime... */
	}
};

