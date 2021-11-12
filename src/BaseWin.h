#pragma once
#include "Bits.h"
#include <iostream>

class BaseWin
{
public:
    HINSTANCE hInst;
    HWND hWnd;
    HWND Parent;
    int ID;
    Point Position;
    Size size;

    // no need
    BaseWin() = delete;

    BaseWin(HWND _parent, const Point& pos, const Size& _size, int id, HINSTANCE _hInst)
        :Parent(_parent), Position(pos), size(_size), ID(id), hInst(_hInst)
    { /* heh */ }

    void Show(bool show = true)
    {
        ShowWindow(hWnd, 5 * show); // sw_show == 5, sw_hide == 0
    }

    void Destroy()
    {
        DestroyWindow(hWnd);
    }
};