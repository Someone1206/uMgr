#include "Button.h"

Button::Button(HWND _parent, int id, LPCSTR txt, const Point& pos, const Size& size, int styles)
	:BaseWin(pos, size, _parent), text(txt)
{
	hwnd = CreateWindowEx(
		0,
		"buTTon", text, styles,
		pos.x, pos.y, size.x, size.y,
		parent, (HMENU)id, GetModuleHandle(nullptr), nullptr
	);

	Show();
}
