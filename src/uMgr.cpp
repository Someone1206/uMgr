#include "Window.h"

class MainWindow
	:public Window
{
public:
	MainWindow()
		:Window(nullptr, funtion, "kk", Point(), Size())
	{
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