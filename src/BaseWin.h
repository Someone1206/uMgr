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
        INT choice; // y not?
        if (show)
            choice = SW_SHOW;
        else
            choice = SW_HIDE;
        ShowWindow(hWnd, choice);
    }

    void Destroy()
    {
        DestroyWindow(hWnd);
    }
};