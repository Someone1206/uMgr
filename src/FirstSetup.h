#pragma once
#include <wx/wx.h>
#include "ufw/GV.h"

class FirstSetup
    :public wxFrame
{
private:
    char len = 0;
    bool change_folderPerm = false;

    wxString __choices[3];
    wxString paf_selected = uFolder, _this_paf;

    wxTextCtrl* details = nullptr, * __paf_sel = nullptr, * pwd = nullptr, * re_pwd = nullptr;
    wxChoice* paf_fr_data = nullptr;

    wxBoxSizer* pwd_sizer = nullptr;
    wxButton* browse_btn = nullptr;

    std::string str_in_uPaf = ("Your logs will be stored in the following folder:\n" + uFolder + "\nThis is the recommended"
        "path since your logs will be safe from intruders\n(other users on your OS) via your OS itself.");


    enum {
        DET_TXT_CTRL,
        PAF_TXT_CTRL,
        PAF_CHOICES,
        BTN_BROWSE,
        ADD_PWD,
        ID_PWD,
        ID_RE_PWD,
        ID_GO,
        ID_CANCEL
    };
public:
    FirstSetup(const wxString& thisPaf);
    
    void choice(wxCommandEvent& evt);
    void browse(wxCommandEvent& evt);
    void a_pwd(wxCommandEvent& evt);
    void go(wxCommandEvent& evt);
    void cancel(wxCommandEvent& evt);
    
    wxDECLARE_EVENT_TABLE();

    ~FirstSetup();
};