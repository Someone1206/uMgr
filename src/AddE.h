#pragma once
#include <wx/wx.h>
#include "ufw/fileIO.h"

class AddE :
    public wxFrame
{
public:
    AddE(wxWindow* frame, const wxString& title, ReadOptions readOption, const wxString& entryName, const wxPoint& pos, const wxSize& size);

private:
    wxWindow* __frame = nullptr;

    wxTextCtrl* date = nullptr;
    wxTextCtrl* time = nullptr;
    wxTextCtrl* param1 = nullptr;    // param1 for anime -> Season, manga -> Chapter, movies -> Part
    wxTextCtrl* param2 = nullptr;    // param2 for anime -> episode, manga -> page stopped on
    wxTextCtrl* details = nullptr;

    ~AddE();
};

