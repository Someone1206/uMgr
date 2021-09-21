#include "NumCtrl.h"

BEGIN_EVENT_TABLE(NumCtrl, wxTextCtrl)
    EVT_KEY_DOWN(NumCtrl::onType)
    EVT_KEY_UP(NumCtrl::onType)
END_EVENT_TABLE()

NumCtrl::NumCtrl(wxWindow* parent, wxWindowID id, const wxString& s, long style)
{
    bool idk = Create(parent, id, s, wxDefaultPosition, wxDefaultSize, style);
    SetMaxLength(9);
}

void NumCtrl::onType(wxKeyEvent& evt)
{
    switch (evt.GetKeyCode())
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case WXK_NUMPAD0:
    case WXK_NUMPAD1:
    case WXK_NUMPAD2:
    case WXK_NUMPAD3:
    case WXK_NUMPAD4:
    case WXK_NUMPAD5:
    case WXK_NUMPAD6:
    case WXK_NUMPAD7:
    case WXK_NUMPAD8:
    case WXK_NUMPAD9:

    case WXK_BACK:
    case WXK_RETURN:
    case WXK_DELETE:
    case WXK_CLEAR:
    case WXK_SHIFT:
    case WXK_END:
    case WXK_HOME:
    case WXK_LEFT:
    case WXK_UP:
    case WXK_RIGHT:
    case WXK_DOWN:
    case WXK_SELECT:
    case WXK_PAGEUP:
    case WXK_PAGEDOWN:
        evt.Skip();
    }
}
