#pragma once
#include "BaseWin.h"

// ofcourse copied from ChiliTomatoNoodle's youtube video on
// encapsulating the window creation in dx12 --> Creating a Windows Framework

class Window :
    public BaseWin
{
private:
	class WndClass
	{
	public:
        static LPCSTR getName() noexcept;
        static HINSTANCE getHInst() noexcept;
	private:
		WndClass();
		~WndClass();

        static constexpr LPCSTR WndC_Name = "some wondow";
        static WndClass wndClass;
        HINSTANCE hInst;
	};

public:
    Window(int width, int height, LPCSTR name)noexcept;

private:
    static LRESULT CALLBACK msgSetup(HWND _hwnd, UINT msg, WPARAM wParam, LPARAM lParam)noexcept;
    static LRESULT CALLBACK msgThunk(HWND _hwnd, UINT msg, WPARAM wParam, LPARAM lParam)noexcept;
    LRESULT HandleMsg(HWND _hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

public:
    ~Window();
};

