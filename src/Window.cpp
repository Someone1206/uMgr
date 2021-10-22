#include "Window.h"

Window::WndClass Window::WndClass::wndClass;

LPCSTR Window::WndClass::getName() noexcept
{
	return WndC_Name;
}

HINSTANCE Window::WndClass::getHInst() noexcept
{
	return wndClass.hInst;
}

Window::WndClass::WndClass()
	:hInst(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = msgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = getHInst();
	wc.hIcon = nullptr;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = getName();
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);
}

Window::WndClass::~WndClass()
{
	UnregisterClass(WndC_Name, getHInst());
}

Window::Window(int width, int height, LPCSTR name) noexcept
{
	hwnd = CreateWindowEx(
		0,
		WndClass::getName(), name,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height,
		nullptr, nullptr, WndClass::getHInst(), this
	);
}

LRESULT Window::msgSetup(HWND _hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const create = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const wnd = static_cast<Window*>(create->lpCreateParams);
		SetWindowLongPtr(_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(wnd));
		SetWindowLongPtr(_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::msgThunk));
		return wnd->HandleMsg(_hwnd, msg, wParam, lParam);
	}
	return DefWindowProc(_hwnd, msg, wParam, lParam);
}

LRESULT Window::msgThunk(HWND _hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	Window* const wnd = reinterpret_cast<Window*>(GetWindowLongPtr(_hwnd, GWLP_USERDATA));
	return wnd->HandleMsg(_hwnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND _hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(69);
		break;
	default:
		break;
	}
	return DefWindowProc(_hwnd, msg, wParam, lParam);
}

Window::~Window()
{
	Destroy();
}
