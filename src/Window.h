#pragma once
#include "BaseWin.h"

template <class DERIVED_TYPE>
class Window :
    public BaseWin
{
public:
    int returnValue;
private:
    static constexpr LPCSTR className = "The best window in the entire world";
    void(*wndProc)(HWND, UINT, WPARAM, LPARAM);

public:
    Window(HWND parent, LPCSTR title, const Point& pos, const Size& size,
        int styles = WS_OVERLAPPEDWINDOW, int retVal = 69, bool _disable_par = false
    );
public:
    ~Window();

public:
    static LRESULT CALLBACK WndProc(HWND _hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
};

