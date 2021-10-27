#pragma once
#include "BaseWin.h"

class Button :
    public BaseWin
{
    LPCSTR text;
public:
    Button(HWND _parent, int id, LPCSTR txt = "", 
        const Point& pos = Point(), const Size& size = Size(), 
        int styles = WS_CHILD
    );

    ~Button() 
    { /**/ }
};

Button::Button(HWND _parent, int id, LPCSTR txt, const Point& pos, const Size& size, int styles)
    :BaseWin(pos, size, _parent), text(txt)
{
    hwnd = CreateWindowEx(
        0,
        "buTTon", text, styles,
        pos.x, pos.y, size.x, size.y,
        parent, (HMENU)id, GetModuleHandle(nullptr), nullptr
    );

    Show();
}