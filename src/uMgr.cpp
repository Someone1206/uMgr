#include "Window.h"
#include "Button.h"

#define normWinStyle WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU


class AboutWindow
    :public Window<AboutWindow>
{
private:
    HWND txt;
public:
    AboutWindow(HWND parent);

    LRESULT HandleMessages(UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch (msg)
        {
        case WM_CLOSE:
            EnableWindow(this->Parent, TRUE);
            Destroy();
            break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint( this->hWnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
            EndPaint(this->hWnd, &ps);
            break;
        }
        }
        return DefWindowProc(this->hWnd, msg, wParam, lParam);
    }
};

AboutWindow::AboutWindow(HWND parent)
    :Window(parent, "About Me", 20, Point(), Size(), WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WIN_DETACH_PAR, -69)
{
    EnableWindow(this->Parent, FALSE);
    txt = CreateWindowEx(
        0,
        "edIt", "",
        WS_CHILD, 1, 1, 50, 50,
        this->hWnd, (HMENU)12, this->hInst, nullptr
    );
    ShowWindow(txt, SW_SHOW);
}


class MainWindow
    :public Window<MainWindow>
{
private:
    HMENU menuBar;
    HMENU menuIt;

    enum
    {
        BTN_KILL,
        BTN_NEWwIN,
        M_QUIT,
        M_ADD_LOG,
        M_ABT
    };
public:
    MainWindow()
        :Window<MainWindow>(nullptr, "Useless Manger", -1, Point(), Size(640, 480), WS_OVERLAPPEDWINDOW)
    {
        Button* btn = new Button(hWnd, -1, "Kill Me", Point(), Size(300, 100));
        UpdateWindow(btn->hWnd);
        Button btn1(hWnd, BTN_NEWwIN, "New Window", Point(310, 0), Size(280, 100));

        menuBar = CreateMenu();
        menuIt = CreateMenu();
        AppendMenu(menuIt, MF_ENABLED, M_ADD_LOG, "Add Log");
        AppendMenu(menuBar, MF_ENABLED | MF_STRING, M_QUIT, "Quit");
        AppendMenu(menuBar, MF_ENABLED | MF_STRING, M_ABT,"About Me");
        AppendMenu(menuBar, MF_POPUP, (UINT_PTR)menuIt, "Add");

        SetMenu(hWnd, menuBar);
    }


    LRESULT HandleMessages(UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch (msg)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
            EndPaint(hWnd, &ps);
            break;
        }
        case WM_COMMAND:
            if (LOWORD(wParam) == BTN_KILL)
            {
                PostQuitMessage(this->returnValue);
                break;
            }
            else if (LOWORD(wParam) == M_ABT)
            {
                AboutWindow* abt = new AboutWindow(this->hWnd);
                abt->Show();
            }
        }

        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
};


int CALLBACK WinMain(
    HINSTANCE hInst,
    HINSTANCE h_p_Inst,
    LPSTR     nCmdLine,
    int       nCmdShow)
{
    MainWindow* window = new MainWindow();
    window->Show();

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
