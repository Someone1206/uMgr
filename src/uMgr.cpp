#include "Window.h"
#include "Button.h"

class MainWindow
	:public Window
{
public:
	MainWindow()
		:Window(nullptr, funtion, "kk", Point(), Size())
	{
		Button* btn = new Button(this->hwnd, 1, "Just do it", Point(), Size(500, 100));
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
			PostQuitMessage(02);
			break;
		case WM_COMMAND:
			if (LOWORD(wParam) == 1)
			{
				MessageBox(_hwnd, "Thanks for killing me!", "Thanks", MB_OKCANCEL | MB_USERICON);
				PostQuitMessage(69);
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
	LPCSTR className = "main window";

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