#pragma once
#include <Windows.h>

class Point
{
public:
	int x = 0, y = 0;
	Point(int _x = CW_USEDEFAULT, int _y = CW_USEDEFAULT);

	Point operator+(const Point& pt);
	Point operator-(const Point& pt);

	~Point();
};

inline Point::Point(int _x, int _y)
{
	x = _x;
	y = _y;
}

inline Point Point::operator+(const Point& pt)
{
	Point res;
	res.x = x + pt.x;
	res.y = y + pt.y;
	return res;
}

inline Point Point::operator-(const Point& pt)
{
	Point res;
	res.x = x - pt.x;
	res.y = y - pt.y;
	return res;
}

inline Point::~Point()
{
	// watch anime.
}

