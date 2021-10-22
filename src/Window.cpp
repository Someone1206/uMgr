#include "Window.h"

Window::Window(HWND parent, void(*_wndProc)(HWND _hwnd, UINT msg, WPARAM wParam, LPARAM lParam),
	LPCSTR title, const Point& pos, const Size& size,
	int styles, int retVal)
	:BaseWin(pos, size), returnValue(retVal), hInst(GetModuleHandle(nullptr))
{
    if (_wndProc == nullptr)
    {
        /*
        * wut it should be:
        * [this](HWND _hwnd, UINT msg, WPARAM wParam, LPARAM lParam)->void
        * {
        *     switch (msg)
        *     {
        *     case WM_CLOSE:
        *         PostQuitMessage(returnValue);
        *         break;
        *     }
        * };
        *
        * but gives this error
        * Severity	Code	Description	Project	File	Line	Suppression State
        * Error (active)	E0413	no suitable conversion function from
        * "lambda []void (HWND _hwnd, UINT msg, WPARAM wParam, LPARAM lParam)->void"
        * to "void (*)(HWND, UINT, WPARAM, LPARAM)" exists	uMgr	D:\Me\Me\ZOthers\uMgr\src\testWindow.cpp	22
        *
        * Probably will work on it some day later
        *
        */
        wndProc = [](HWND _hwnd, UINT msg, WPARAM wParam, LPARAM lParam)->void
        {
            switch (msg)
            {
            case WM_CLOSE:
                // PostQuitMessage(0);
                // don't quit the entire application
                break;
            }
        };
    }
    else
        wndProc = _wndProc;

    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(wc);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = msgSetup;
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

    hwnd = CreateWindowEx(
        0,
        className, title,
        styles,
        pos.x, pos.y, size.x, size.y,
        parent, nullptr, hInst, this
    );
}

LRESULT Window::msgSetup(HWND _hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_NCCREATE)
    {
        const CREATESTRUCTW* const createSt = reinterpret_cast<CREATESTRUCTW*>(lParam);
        Window* const wnd = static_cast<Window*>(createSt->lpCreateParams);
        SetWindowLongPtr(_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(wnd));
        SetWindowLongPtr(_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::msgThunk));
        return wnd->windowProc(_hwnd, msg, wParam, lParam);
    }
    return DefWindowProc(_hwnd, msg, wParam, lParam);
}

LRESULT Window::msgThunk(HWND _hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Window* const wnd = reinterpret_cast<Window*>(GetWindowLongPtr(_hwnd, GWLP_USERDATA));
    return wnd->windowProc(_hwnd, msg, wParam, lParam);
}

LRESULT Window::windowProc(HWND _hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    wndProc(_hwnd, msg, wParam, lParam);
    return DefWindowProc(_hwnd, msg, wParam, lParam);
}

Window::~Window()
{
    UnregisterClass(className, hInst);
    Destroy();
}
