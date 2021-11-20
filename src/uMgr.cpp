#include "Window.h"
#include "Button.h"
#include "ComboBox.h"
#include "About.h"
#include <fstream>

#define normWinStyle WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU


class MainWindow
    :public Window<MainWindow>
{
private:
    HMENU menuBar;
    HMENU menuIt;
    ComboBox* genres = nullptr;
    std::string* paf_list = new std::string[5];

    Button* btn_kill = nullptr, * cls_cbox = nullptr;

    enum
    {
        BTN_KILL,
        BTN_CLS,
        M_QUIT,
        M_ADD_LOG,
        M_ABT,
        CB_GEN
    };
public:
    MainWindow()
        :Window<MainWindow>(nullptr, "Useless Manger", -1, Point(), Size(640, 480), WS_OVERLAPPEDWINDOW)
    {
        btn_kill = new Button(hWnd, BTN_KILL, "Kill Me", Point(), Size(300, 100));
        btn_kill->Show(1);
        //Button btn1(hWnd, BTN_CLS, "クリア ComboBox", Point(310, 0), Size(280, 100));
        cls_cbox = new Button(this->hWnd, BTN_CLS, "クリア ComboBox", Point(310, 0), Size(280, 100));

        menuBar = CreateMenu();
        menuIt = CreateMenu();
        AppendMenu(menuIt, MF_ENABLED, M_ADD_LOG, "Add Log");
        AppendMenu(menuBar, MF_ENABLED | MF_STRING, M_QUIT, "Quit");
        AppendMenu(menuBar, MF_ENABLED | MF_STRING, M_ABT,"About Me");
        AppendMenu(menuBar, MF_POPUP, (UINT_PTR)menuIt, "Add");

        genres = new ComboBox(this->hWnd, Point(10, 120), Size(100, -1), CB_GEN);
        {
            std::ifstream file(("uMgrData\\GenreIndex.baka"));
            genres->updateList_A(file, paf_list, true);
        }
        SetMenu(hWnd, menuBar);
        //MessageBox(this->hWnd, genres->getTxt(0).c_str(), "やったね！", MB_OKCANCEL | MB_ICONINFORMATION);
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
                About* abt = new About(this->hWnd);
                abt->Show();
            }
            else if (LOWORD(wParam) == BTN_CLS)
            {
                genres->Clear();
            }
            else if (HIWORD(wParam) == CBN_SELCHANGE)
            {
                // later
            }
            break;
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
