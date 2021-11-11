#include "BaseWin.h"
#include <iostream>

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
        :BaseWin(parent, pos, _size, id), returnValue(retVal)
    {
        WNDCLASSEX wc = { 0 };

        wc.cbSize = sizeof(wc);
        wc.style = CS_OWNDC;
        wc.lpfnWndProc = D_CLASS::WndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = GetModuleHandle(nullptr);
        wc.hIcon = nullptr;
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hbrBackground = nullptr;
        wc.lpszMenuName = nullptr;
        wc.lpszClassName = className;
        wc.hIconSm = nullptr;

        RegisterClassEx(&wc);
        UpdateWindow(this->hWnd);

        HMENU _id = nullptr;
        if (!((styles & WS_CHILD) != WS_CHILD || id == -1))
            _id = (HMENU)ID;

        hWnd = CreateWindowEx(
            stylesEx,
            className, title,
            styles,
            Position.x, Position.y, size.x, size.y,
            parent, _id, GetModuleHandle(nullptr), this
        );

    }
    
    ~Window()
    {
        UnregisterClass(className, GetModuleHandle(nullptr));
        Destroy();
    }
};