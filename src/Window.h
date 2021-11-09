#include "BaseWin.h"

template<class D_CLASS>
class Window
    :public BaseWin
{
public:
    int returnValue;
private:
    static constexpr LPCSTR className = "Best Window in the UNIVERSE!";
public:
    Window(HWND parent, LPCSTR title, int id, const Point& pos, const Size& _size,
        int styles = WS_OVERLAPPEDWINDOW, int retVal = 69, int stylesEx = 0
    );

    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    // declare this fn in the inherited class and use as wnd proc
    virtual LRESULT HandleMessages(UINT msg, WPARAM wParam, LPARAM lParam) = 0;

    ~Window()
    {
        UnregisterClass(className, GetModuleHandle(nullptr));
        Destroy();
    }
};