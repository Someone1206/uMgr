#pragma once
#include <wx/wx.h>
#include "ufw/fileIO.h"

class FirstSetup
    : public wxFrame
{
public:
    FirstSetup(const wxString& title, const wxString& this_paf);

private:
    char len = 3;

    wxChoice* paf_fr_data = nullptr;

    wxButton* go_btn = nullptr;
    wxButton* browse_btn = nullptr;

    wxTextCtrl* pwd = nullptr;
    wxTextCtrl* re_pwn = nullptr;

    void choice(wxCommandEvent& evt);
    void go(wxCommandEvent& evt);
    wxDECLARE_EVENT_TABLE();

    enum 
    {
        ID_CHOICES,
        ID_GO,
        ID_BROWSE
    };
};

