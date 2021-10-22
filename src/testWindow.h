#pragma once
#include "BaseWin.h"

class testWindow :
    public BaseWin
{
public:
    int returnValue;
private:
    static constexpr LPCSTR className = "some class";
    HINSTANCE hInst;
    void(*wndProc)(HWND, UINT, WPARAM, LPARAM);

public:
    testWindow(HWND parent, void (*_wndProc)(HWND _hwnd, UINT msg, WPARAM wParam, LPARAM lParam),
        LPCSTR title, const Point& pos, const Size& size,
        int styles = WS_OVERLAPPEDWINDOW, int retVal = 69
    );

private:
    static LRESULT CALLBACK msgSetup(HWND _hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
    static LRESULT CALLBACK msgThunk(HWND _hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
    LRESULT windowProc(HWND _hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
    ~testWindow();
};

