#pragma once
#include <wx/wx.h>

class FirstSetup
    : public wxFrame
{
public:
    FirstSetup(const wxString& title, const wxString& this_paf, bool& init);

private:
    char len = 3;
    bool* __init;
    bool do_smth = 0;
    wxString __choices[3];
    wxString _this_paf;
    wxString paf_selected = "";

    wxStaticText* __paf_sel = nullptr;
    wxStaticText* details = nullptr;

    wxChoice* paf_fr_data = nullptr;

    wxButton* go_btn = nullptr;
    wxButton* cancel_ = nullptr;
    wxButton* browse_btn = nullptr;

    wxTextCtrl* pwd = nullptr;
    wxTextCtrl* re_pwd = nullptr;

    wxStaticText* pwdtxt = nullptr;
    wxStaticText* pwdtxt2 = nullptr;

    void choice(wxCommandEvent& evt);
    void browse(wxCommandEvent& evt);
    void a_pwd(wxCommandEvent& evt);
    void go(wxCommandEvent& evt);
    void cancel(wxCommandEvent& evt);
    wxDECLARE_EVENT_TABLE();

    enum 
    {
        ID_CHOICES,
        ID_GO,
        ID_CANC,
        ID_BROWSE,
        ID_A_PWD_,
        ID_PWD,
        ID_RE_PWD
    };
};

