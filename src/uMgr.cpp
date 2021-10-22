#include "Window.h"
#include "testWindow.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void smeFn(HWND _hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(69);
		break;
	}
}

int CALLBACK WinMain(
	HINSTANCE hInst,
	HINSTANCE h_p_Inst,
	LPSTR     nCmdLine,
	int       nCmdShow)
{
	LPCSTR className = "main window";
	
	testWindow t(nullptr, nullptr, "lll", Point(), Size());
	t.Show();

	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return msg.wParam;
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	smeFn(hwnd, msg, wParam, lParam);
	return DefWindowProc(hwnd, msg, wParam, lParam);
}