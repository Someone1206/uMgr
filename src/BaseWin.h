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

    uint8_t percentX_S = 0, percentY_S = 0,
            /* percentages for sizes */
            percentX_P = 0, percentY_P = 0
            /* percentages for positions */;

    // no need
    BaseWin() = delete;

    BaseWin(HWND _parent, const Point& pos, const Size& _size, int id, HINSTANCE _hInst)
        :Parent(_parent), Position(pos), size(_size), ID(id), hInst(_hInst)
    { /* heh */ }

    SetPercent(const Size& parentSize) {
        percentX_S = (size.x * 100) / parentSize.x;
        percentY_S = (size.y * 100) / parentSize.y;
        percentX_P = (Position.x * 100) / parentSize.x;
        percentY_P = (Position.y * 100) / parentSize.y;
    }

    void Show(bool show = true)
    {
        ShowWindow(hWnd, 5 * show); // sw_show == 5, sw_hide == 0
    }

    void Destroy()
    {
        DestroyWindow(hWnd);
    }

    void Resize(const Size& parentSize, const Point& pos) {
        MoveWindow(hWnd, pos.x, pos.y, (int)(percentX_S / 100.0 * parentSize.x), (int)(percentY_S / 100.0 * parentSize.y), TRUE);
    }

    void Resize(const Size& parentSize) {
        Resize(parentSize, Point((int)(percentX_P / 100.0 * parentSize.x), (int)(percentY_P / 100.0 * parentSize.y)));
    }

    static constexpr char SEP = (char)1;
};