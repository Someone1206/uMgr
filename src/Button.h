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

