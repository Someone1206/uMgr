#include "Window.h"

template<class D_CLASS>
Window<D_CLASS>::Window(HWND parent, LPCSTR title, int id, const Point& pos, const Size& _size,
    int styles, int retVal, int stylesEx)
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

    hWnd = CreateWindowEx(
        stylesEx,
        className, title,
        styles,
        Position.x, Position.y, size.x, size.y,
        parent, (HMENU)ID, GetModuleHandle(nullptr), this
    );
}

template<class D_CLASS>
LRESULT Window<D_CLASS>::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    D_CLASS* p_this = nullptr;
    if (msg == WM_NCCREATE) {
        CREATESTRUCT* create = (CREATESTRUCT*)lParam;
        p_this = (D_CLASS*)create->lpCreateParams;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)p_this);
        //p_this->hWnd = hwnd;
    }
    else
        p_this = (D_CLASS*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

    if (p_this)
        return p_this->HandleMessages(msg, wParam, lParam);
    else
        return DefWindowProc(hWnd, msg, wParam, lParam);
}
