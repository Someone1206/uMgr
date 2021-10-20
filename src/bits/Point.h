#pragma once
#include <Windows.h>

class Point
{
public:
	int x = 0, y = 0;
	Point(int _x = CW_USEDEFAULT, int _y = CW_USEDEFAULT);

	Point operator+(Point& pt);
	Point operator-(Point& pt);

	~Point();
};

Point::Point(int _x, int _y)
{
}

inline Point Point::operator+(Point& pt)
{
	pt.x = x + pt.x;
	pt.y = y + pt.y;
	return pt;
}

inline Point Point::operator-(Point& pt)
{
	pt.x = x - pt.x;
	pt.y = y - pt.y;
	return pt;
}

Point::~Point()
{
	// watch anime?
}

