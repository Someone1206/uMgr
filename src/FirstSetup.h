#pragma once
#include <wx/wx.h>
#include "ufw/GV.h"

class FirstSetup
    : public wxFrame
{
public:
    FirstSetup(const wxString& title, const wxString& this_paf, bool& init);

private:
    char len = 3;
    bool* __init;
    wxString __choices[3];
    wxString _this_paf;
    wxString paf_selected = "";
    wxString det_str = "Your logs will be stored in the following directory:\n"
                    "" + GV::consts::uPaf.string() + FSEP + GV::consts::user_data_folder + ""
                    "\nThis is the recommended path since your logs will be safe from intruders (other "
                    "users on your OS) via the filesystem\n"
                    "";

    wxStaticText* __paf_sel = nullptr;
    wxStaticText* details = nullptr;

    wxChoice* paf_fr_data = nullptr;

    wxButton* go_btn = nullptr;
    wxButton* cancel_ = nullptr;
    wxButton* browse_btn = nullptr;

    wxTextCtrl* pwd = nullptr;
    wxTextCtrl* re_pwd = nullptr;

    void choice(wxCommandEvent& evt);
    void browse(wxCommandEvent& evt);
    void go(wxCommandEvent& evt);
    void cancel(wxCommandEvent& evt);
    wxDECLARE_EVENT_TABLE();

    enum 
    {
        ID_CHOICES,
        ID_GO,
        ID_CANC,
        ID_BROWSE,
        ID_PWD,
        ID_RE_PWD
    };
};

