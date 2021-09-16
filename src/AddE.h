#pragma once
#include <wx/wx.h>
#include "ufw/fileIO.h"

class AddE :
    public wxFrame
{
public:
    AddE(wxWindow* frame, const wxString& title, ReadOptions readOption, const wxSize& size);

private:

    wxTextCtrl* name = nullptr;
    wxTextCtrl* date = nullptr;
    wxTextCtrl* time = nullptr;
    wxTextCtrl* param1 = nullptr;    // param1 for anime -> Season, manga -> Chapter, movies -> Part
    wxTextCtrl* param2 = nullptr;    // param2 for anime -> episode, manga -> page stopped on
    wxTextCtrl* details = nullptr;

    ~AddE();
};

