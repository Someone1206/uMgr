#pragma once
#include <wx/wx.h>

class About :
    public wxFrame
{
public:
    About(wxWindow* frame, const wxPoint& pos, const wxSize& size, wxColor* theme);

private:
    //wxPanel* win = nullptr;
    //wxStaticText* abt = nullptr;
    wxButton* okBtn = nullptr;

    //wxGridSizer* psizer = nullptr;
    /*
    wxBoxSizer* psizer = nullptr;
    wxBoxSizer* msizer = nullptr;
    */

    void okei(wxCommandEvent& evt); // not to be confused with okei in shinchan

    wxDECLARE_EVENT_TABLE();

public:
    ~About();
};

enum {
    ID_PANEL,
    ID_OK_BTN
};