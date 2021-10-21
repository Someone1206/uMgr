#pragma once
#include "Bits.h"

class BaseWin
{
public:
	HWND hwnd;

	void Show(bool _show = true);
	void Enable(bool _enable = true);
	void Destroy();
};

