#pragma once
#include "Window.h"
#include "TxtBox.h"

class About :
    public Window<About>
{
private:
    TxtBox *txtArea;

    enum {
        ID_TXT
    };
public:
    About(HWND parent, const Size& _size);

    LRESULT HandleMessages(UINT msg, WPARAM wParam, LPARAM lParam);
};

About::About(HWND parent, const Size& _size)
    :Window<About>(nullptr, "About Me", -1, Point(), _size)
{
    std::string txt = "This is a Manager, made by a stupid 15 y/o kid\r\n"
                        "You can use it to log your stuffs like your reviews, thoughts and feelings.\r\n"
                        "You can also use it as a bookmark(rather progress mark)for the last page you"
                        " read in a Book or the last episode(even the time till which) you watched"
                        " in an Anime/Series.\r\n Also it keeps these logs kinda safe(so don't feel"
                        " unsafe storing those Ero-Anime stuffs...)";

    txtArea = new TxtBox(this->hWnd, txt, Point(), Size(), ID_TXT, 
        ES_MULTILINE | WS_VSCROLL | ES_READONLY | ES_CENTER
    );
}

LRESULT About::HandleMessages(UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_SIZE:
        txtArea->Resize(
            Size(LOWORD(lParam) - 10, HIWORD(lParam) - 20),
            Point(10, 10)
        );
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(this->hWnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        EndPaint(this->hWnd, &ps);
        break;
    }
    case WM_COMMAND:
        txtArea->manageFns(wParam, lParam);
        break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}