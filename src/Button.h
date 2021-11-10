#pragma once
#include "BaseWin.h"

class Button
    :public BaseWin
{
public:
    Button(HWND parent, int id, LPCSTR text, const Point& pos, const Size& _size, int styles = WS_CHILD);
    ~Button();
};

Button::Button(HWND parent, int id, LPCSTR text, const Point& pos, const Size& _size, int styles)
    :BaseWin(parent, pos, size, id)
{
    hWnd = CreateWindowEx(
        0,
        "buTTon", text, styles,
        pos.x, pos.y,
        _size.x, _size.y,
        parent, (HMENU)ID, GetModuleHandle(nullptr), nullptr
    );

    Show();
}

Button::~Button()
{
}