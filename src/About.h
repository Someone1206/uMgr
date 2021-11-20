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
    About(HWND parent);

    LRESULT HandleMessages(UINT msg, WPARAM wParam, LPARAM lParam);
};

About::About(HWND parent)
    :Window(nullptr, "About Me", -1, Point(), Size(500, 500))
{
    std::string txt = "some txt\r\nsome txt\r\nsome txt\r\n";

    txtArea = new TxtBox(this->hWnd, txt, Point(), Size(), ID_TXT, 
        ES_MULTILINE | WS_VSCROLL | ES_READONLY | ES_CENTER
    );
}

LRESULT About::HandleMessages(UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_SIZE:
        MoveWindow(
            txtArea->hWnd,
            0, 0,
            LOWORD(lParam), 
            HIWORD(lParam),
            TRUE
        );
        break;
    case WM_COMMAND:
        txtArea->manageFns(wParam, lParam);
        break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}