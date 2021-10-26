#pragma once
#include "BaseWin.h"
class Window :
    public BaseWin
{
public:
    int returnValue;
    bool enablePar = false, disable_par = false;
private:
    static constexpr LPCSTR className = "The best window in the entire world";
    HINSTANCE hInst;
    void(*wndProc)(HWND, UINT, WPARAM, LPARAM);

public:
    Window(HWND parent, void(*_wndProc)(HWND _hwnd, UINT msg, WPARAM wParam, LPARAM lParam),
        LPCSTR title, const Point& pos, const Size& size,
        int styles = WS_OVERLAPPEDWINDOW, int retVal = 69, bool _disable_par = false
    );

private:
    static LRESULT CALLBACK msgSetup(HWND _hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK msgThunk(HWND _hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT windowProc(HWND _hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
    ~Window();
};

