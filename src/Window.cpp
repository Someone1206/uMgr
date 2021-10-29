#include "Window.h"

template<class DERIVED_TYPE>
Window<DERIVED_TYPE>::Window(HWND _parent, LPCSTR title, const Point& pos, const Size& size,
    int styles, int retVal, bool _disable_par)
    :BaseWin(pos, size, _parent), returnValue(retVal)
{
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(wc);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = DERIVED_TYPE::WindowProc;
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

    hwnd = CreateWindowEx(
        0,
        className, title,
        styles,
        pos.x, pos.y, size.x, size.y,
        parent, nullptr, GetModuleHandle(nullptr), this
    );
}

template<class DERIVED_TYPE>
Window<DERIVED_TYPE>::~Window()
{
    UnregisterClass(className, GetModuleHandle(nullptr));
    Destroy();
}

template<class DERIVED_TYPE>
LRESULT Window<DERIVED_TYPE>::WndProc(HWND _hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    DERIVED_TYPE* pThis = NULL;
    if (msg == WM_NCCREATE)
    {
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
        pThis->m_hwnd = hwnd;
    }
    else
    {
        pThis = (DERIVED_TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }
    if (pThis)
    {
        return pThis->HandleMessage(msg, wParam, lParam);
    }
    else
    {
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

}
