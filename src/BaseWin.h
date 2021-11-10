#pragma once
#include "Bits.h"

class BaseWin
{
public:
    HWND hWnd;
    HWND Parent;
    int ID;
    Point Position;
    Size size;

    // no need
    BaseWin() = delete;

    BaseWin(HWND _parent, const Point& pos, const Size& _size, int id)
        :Parent(_parent), Position(pos), size(_size), ID(id)
    { /* heh */
    }

    void Show(bool show = true)
    {
        if (show)
            ShowWindow(hWnd, SW_SHOW);
        else
            ShowWindow(hWnd, SW_HIDE);
    }

    void Destroy()
    {
        DestroyWindow(hWnd);
    }
};