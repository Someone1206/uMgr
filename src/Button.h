#pragma once
#include "BaseWin.h"

class Button
    :public BaseWin
{
public:
    Button(HWND parent, int id, LPCSTR text, const Point& pos, const Size& _size, int styles = WS_CHILD, HINSTANCE _hInst = GetModuleHandle(nullptr));
    ~Button();
};

Button::Button(HWND parent, int id, LPCSTR text, const Point& pos, const Size& _size,
    int styles, HINSTANCE _hInst)
    :BaseWin(parent, pos, _size, id, _hInst)
{
    hWnd = CreateWindowEx(
        0,
        "buTTon", text, styles,
        Position.x, Position.y,
        size.x, size.y,
        Parent, (HMENU)ID, hInst, nullptr
    );
    Show();
}

Button::~Button()
{
}