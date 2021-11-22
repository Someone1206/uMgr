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
    HMENU menu_add;
    HMENU menu_edit;
    HMENU menu_abt;
    ComboBox* genres = nullptr;
    std::string* paf_list;

    Button* last10logs = nullptr, * allLogs = nullptr, * addLog = nullptr;

    enum
    {
        // btn -> button,
        // m -> menu bar,
        // cb -> combobox,
        // t -> text box
        BTN_LL /*last logs*/, BTN_AL /*all logs*/, BTN_ADD /*add log for genre/grp*/,
        CB_GEN /*genres*/,
        M_QUIT,
        M_ADD_LOG, M_ADD_GEN, M_PREF, M_ABT, M_SUP
    };
public:
    MainWindow()
        :Window<MainWindow>(nullptr, "Useless Manger", -1, Point(), Size(640, 480),
        WS_OVERLAPPEDWINDOW)
    {
        last10logs = new Button(hWnd, BTN_LL, "Last 10 Logs", Point(210, 12), Size(170, 40));
        allLogs = new Button(this->hWnd, BTN_AL, "All Logs", Point(430, 15), Size(170, 40));
        addLog = new Button(this->hWnd, BTN_ADD, "Add Log", Point(), Size(0, 0));
        addLog->Show(0);

        genres = new ComboBox(this->hWnd, Point(10, 20), Size(150, -1), CB_GEN);
        {
            genres->Add("Logs");
            std::ifstream file(("uMgrData\\GenreIndex.baka"));
            if(file)
            genres->updateList_A(file, paf_list, true, CB_INIT_PAF);
        }


        // menu bar stuffs

        menuBar = CreateMenu();     // main menu bar
        menuIt = CreateMenu();
        menu_add = CreateMenu();    // menu for add log/add genre (i may rename it to group)
        menu_edit = CreateMenu();   // menu for preferences
        menu_abt = CreateMenu();    // menu for abt me & support

        AppendMenu(menu_add, MF_ENABLED, M_ADD_GEN, "Add Genre");
        AppendMenu(menu_edit, MF_ENABLED, M_PREF, "Preferences");
        AppendMenu(menu_abt, MF_ENABLED, M_ABT, "About Me");
        AppendMenu(menu_abt, MF_ENABLED, M_SUP, "Support Me!");
        AppendMenu(menuIt, MF_ENABLED, M_ADD_LOG, "Add Log");

        AppendMenu(menuBar, MF_POPUP, (UINT_PTR)menu_add, "Add");
        AppendMenu(menuBar, MF_POPUP, (UINT_PTR)menu_edit, "Edit");
        AppendMenu(menuBar, MF_POPUP, (UINT_PTR)menu_abt, "About");
        AppendMenu(menuBar, MF_ENABLED | MF_STRING, M_QUIT, "Quit");

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
            if (LOWORD(wParam) == M_QUIT)
            {
                bool res = MessageBox(this->hWnd, "Wanna Rully Quit?\n何で？", "エーーー",
                    MB_OKCANCEL | MB_ICONWARNING
                );
                if (res)
                    PostQuitMessage(this->returnValue);
                break;
            }
            else if (LOWORD(wParam) == M_ABT)
            {
                About* abt = new About(this->hWnd, Size(300, 150));
                abt->Show();
            }
            else if (HIWORD(wParam) == CBN_SELCHANGE)
            {
                static bool counter = 0;
                unsigned int index = genres->getIndex();
                if (index == 0)
                {
                    if (counter != 0)
                    {
                        RemoveMenu(menu_add, 0, MF_BYPOSITION);
                        addLog->Show(0);
                        last10logs->Show();
                        allLogs->Show();
                        counter = 0;
                    }
                }
                else {
                    if (counter != 1) {
                        RemoveMenu(menu_add, 0, MF_BYPOSITION);
                        AppendMenu(menu_add, MF_ENABLED, M_ADD_LOG, "Add Log");
                        AppendMenu(menu_add, MF_ENABLED, M_ADD_GEN, "Add Genre");

                        addLog->Resize(
                            Size(last10logs->size.x + allLogs->size.x,
                                last10logs->size.y), 
                            Point(last10logs->Position + Point(10, 0))
                        );
                        last10logs->Show(0);
                        allLogs->Show(0);
                        addLog->Show();

                        counter = 1;
                    }
                    MessageBox(this->hWnd, paf_list[index - 1].c_str(), 
                        "Seleted", MB_OKCANCEL | MB_ICONINFORMATION);
                }
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
    int       nCmdShow
)
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