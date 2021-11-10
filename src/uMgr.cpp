#include "Window.h"
#include "Button.h"
//#include "WindowTest.h"

#define normWinStyle WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU
/*
class childWin
    :public Window
{
public:
    childWin(HWND _hwnd)
        :Window(_hwnd, nullptr, "Kill Me", Point(), Size(640, 480), normWinStyle, 69, true)
    {
        HWND t_box = CreateWindowEx(
                WS_EX_CLIENTEDGE,
                "ediT", "Fook",
                WS_CHILD | WS_VISIBLE, 10, 10, 620, 450,
                hwnd, nullptr, nullptr, nullptr);
        cmmt ShowWindow(t_box, SW_SHOW);
        UpdateWindow(t_box);
    }
};
*/
/*
class MainWindow
    :public WindowTest<MainWindow>
{
    // ik its default, but it looks better
private:
    HMENU menuBar;
    HMENU menuIt;

    enum 
    {
        BTN_KILL,
        BTN_NEWwIN,
        M_QUIT,
        M_ADD_LOG
    };
public:
    MainWindow()
        :WindowTest(nullptr, "Useless Manger", -1, Point(CW_USEDEFAULT, CW_USEDEFAULT), Size(640, 480), normWinStyle)
    {
        Button* btn = new Button(this->hwnd, BTN_KILL, "Kill Me", Point(), Size(300, 100));
        UpdateWindow(btn->hwnd);
        Button btn1(this->hwnd, BTN_NEWwIN, "New Window", Point(310, 0), Size(280, 100));

        menuBar = CreateMenu();
        menuIt = CreateMenu();

#if DBUG
        if (menuBar == NULL)
            MessageBox(this->hwnd, "Problems creating menu", "Can't create menu",
                    MB_OK | MB_ICONERROR);
#endif

        AppendMenu(menuIt, MF_ENABLED, M_ADD_LOG, "Add Log");
        if (menuBar != nullptr)
        {
            AppendMenu(menuBar, MF_POPUP, (UINT_PTR)menuIt, "Add");
            AppendMenu(menuBar, MF_ENABLED | MF_STRING, M_QUIT, "Quit");
        }
        SetMenu(this->hwnd, menuBar);
    }

    ~MainWindow()
    {
    }

private:
    LRESULT HandleMessages(UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
            EndPaint(hwnd, &ps);
            break;
        }
        case WM_COMMAND:
            if (LOWORD(wParam) == BTN_KILL)
            {
                PostQuitMessage(this->returnValue);
                break;
            }
        }
        
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
};

*/

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
        M_ADD_LOG
    };
public:
    MainWindow()
        :Window<MainWindow>(nullptr, "Useless Manger", -1, Point(CW_USEDEFAULT, CW_USEDEFAULT), Size(640, 480), normWinStyle)
    {
        Button* btn = new Button(hWnd, BTN_KILL, "Kill Me", Point(), Size(300, 100));
        UpdateWindow(btn->hWnd);
        Button btn1(hWnd, BTN_NEWwIN, "New Window", Point(310, 0), Size(280, 100));

        menuBar = CreateMenu();
        menuIt = CreateMenu();
        AppendMenu(menuIt, MF_ENABLED, M_ADD_LOG, "Add Log");
        AppendMenu(menuBar, MF_ENABLED | MF_STRING, M_QUIT, "Quit");
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
    
    ///MainWindow* newWindow = new MainWindow();
    //newWindow->Show();

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
