#pragma once
#include "BaseWin.h"
#define WIN_DETACH_PAR 0x45 // detach the window from the parent, i.e. 
// window will have a different tab on task bar


template<class D_CLASS>
class Window
    :public BaseWin
{
public:
    int returnValue;
private:
    static constexpr LPCSTR className = "Best Window in the UNIVERSE!";
    //static HWND this_hwnd;
public:
    // declare this fn in the inherited class and use as wnd proc
    virtual LRESULT HandleMessages(UINT msg, WPARAM wParam, LPARAM lParam)
    {
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }


    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        D_CLASS* p_this = nullptr;
        if (msg == WM_NCCREATE) {
            CREATESTRUCT* create = (CREATESTRUCT*)lParam;
            p_this = (D_CLASS*)create->lpCreateParams;
            p_this->hWnd = hwnd;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)p_this);
        }
        else
            p_this = (D_CLASS*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

        if (p_this && p_this->hWnd)
            return p_this->HandleMessages(msg, wParam, lParam);
        else
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    Window(HWND parent, LPCSTR title, int id, const Point& pos, const Size& _size,
        int styles = WS_OVERLAPPEDWINDOW, int retVal = 69, int stylesEx = 0
    )
        :BaseWin(parent, pos, _size, id, GetModuleHandle(nullptr)), returnValue(retVal)
    {
        WNDCLASSEX wc = { 0 };

        wc.cbSize = sizeof(wc);
        wc.style = CS_OWNDC;
        wc.lpfnWndProc = D_CLASS::WndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = hInst;
        wc.hIcon = nullptr;
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hbrBackground = nullptr;
        wc.lpszMenuName = nullptr;
        wc.lpszClassName = className;
        wc.hIconSm = nullptr;

        RegisterClassEx(&wc);
        UpdateWindow(this->hWnd);

        // if you don't care about the id (-1), it'll be nullptr
        HMENU _id = nullptr;
        if (!((styles & WS_CHILD) != WS_CHILD || id == -1))
            _id = (HMENU)ID;

        // if thw window to be created sud have a different tab in the task bar
        HWND hwnd_to_use = Parent;
        if ((styles & WIN_DETACH_PAR) == WIN_DETACH_PAR)
            hwnd_to_use = nullptr;
        // windows sud ignore dis useless value of win_detach_par
        hWnd = CreateWindowEx(
            stylesEx,
            className, title,
            styles,
            Position.x, Position.y, size.x, size.y,
            hwnd_to_use, _id, hInst, this
        );

    }
    
    ~Window()
    {
        UnregisterClass(className, hInst);
        Destroy();
    }
};