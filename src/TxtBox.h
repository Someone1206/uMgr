#pragma once
#include "BaseWin.h"
#include <string>
#include <algorithm>
// #include <boost/algorithm/string/replace.hpp>


#define IDM_EDCOPY    0xbcdefa
#define IDM_EDCUT     0xcdefab
#define TE_FORMAT     0xabcdef
#define TE_COPY       IDM_EDCOPY
#define TE_CUT        IDM_EDCUT

class TxtBox
	:public BaseWin
{
public:

	TxtBox(HWND parent, std::string& content, const Point& pos, 
		const Size& _size, int id, int styles = 0, int stylesEx = 0
	);

	/*
	 * Manage text Box functions like copying, pasting, etc.
	*/
	void manageFns(UINT msg, WPARAM wParam, LPARAM lParam);
	void manageFns(WPARAM wParam, LPARAM lParam);

	~TxtBox() { /* _____ */ };
};

TxtBox::TxtBox(HWND parent, std::string& content, const Point& pos, const Size& _size,
	int id, int styles, int stylesEx)
	:BaseWin(parent, pos, _size, id, GetModuleHandle(nullptr))
{
	if ((styles & TE_FORMAT) == TE_FORMAT) {
		int_fast32_t index = 0;
		for (; index < content.length();)
			if (content.at(index++) == '\n')
			{
				index++;
				content.replace(index - 2, 1, "\r\n");
			}
	}

	hWnd = CreateWindowEx(
		stylesEx,
		"eDiT", nullptr,
		WS_CHILD | WS_VISIBLE | styles,
		Position.x, Position.y,
		size.x, size.y,
		Parent, (HMENU)ID, hInst, nullptr
	);

	Show(true);

	SendMessage(this->hWnd, WM_SETTEXT, 0, (LPARAM)content.c_str());
}


void TxtBox::manageFns(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_COMMAND:
		this->manageFns(wParam, lParam);
	}
}

void TxtBox::manageFns(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case IDM_EDCOPY:
		SendMessage(this->hWnd, WM_COPY, 0, 0);
		return;
	case IDM_EDCUT:
		SendMessage(this->hWnd, WM_CUT, 0, 0);
		return;
	}
}