#include "Window.h"
#include "Button.h"



class childWin
	:public Window
{
public:
	childWin(HWND _hwnd)
		:Window(_hwnd, nullptr, "Kill Me", Point(), Size(640, 480), WS_OVERLAPPEDWINDOW, 69, true)
	{}
};


class MainWindow
	:public Window
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
		:Window(nullptr, funtion, "Useless Manger", Point(), Size(640, 480))
	{
		Button* btn = new Button(this->hwnd, BTN_KILL, "Kill Me", Point(), Size(300, 100));
		Button btn1(this->hwnd, BTN_NEWwIN, "New Window", Point(310, 0), Size(280, 100));

		menuBar = CreateMenu();
		menuIt = CreateMenu();

#if DBUG
		if (menuBar == NULL)
			MessageBox(this->hwnd, "Problems creating menu", "Can't create menu",
					MB_OK | MB_ICONERROR);
#endif

		AppendMenu(menuIt, MF_ENABLED, M_ADD_LOG, "Add Log");

		AppendMenu(menuBar, MF_POPUP, (UINT_PTR)menuIt, "Add");
		AppendMenu(menuBar, MF_ENABLED | MF_STRING, M_QUIT, "Quit");

		SetMenu(this->hwnd, menuBar);
	}

	~MainWindow()
	{
	}

private:
	static void funtion(HWND _hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_CLOSE:
			PostQuitMessage(0x45);
			break;
		case WM_COMMAND:
			if (LOWORD(wParam) == BTN_KILL)
			{
				int choice = MessageBox(_hwnd, "Thanks for killing me!", "Thanks",
						MB_OKCANCEL | MB_USERICON);
				if (choice == IDOK)
					PostQuitMessage(69);
			}
			else if (LOWORD(wParam) == BTN_NEWwIN)
			{
				childWin* win = new childWin(_hwnd);
				win->Show();
			}
			else if (LOWORD(wParam) == M_ADD_LOG)
			{
				MessageBox(_hwnd, "Still in gamma", "not available", MB_OK | MB_ICONEXCLAMATION);
			}
			else if (LOWORD(wParam) == M_QUIT)
			{
				MessageBox(_hwnd, "Bye",
						"!!!!", MB_ICONEXCLAMATION | MB_OK);
				PostQuitMessage(0x45);
			}
		}
	}
};


int CALLBACK WinMain(
	HINSTANCE hInst,
	HINSTANCE h_p_Inst,
	LPSTR     nCmdLine,
	int       nCmdShow)
{
	
	MainWindow* newWindow = new MainWindow();
	newWindow->Show();

	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}