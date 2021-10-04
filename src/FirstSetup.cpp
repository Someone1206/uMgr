#include "FirstSetup.h"
#include "mainFrame.h"

wxBEGIN_EVENT_TABLE(FirstSetup, wxFrame)
    EVT_CHOICE(ID_CHOICES, FirstSetup::choice)
    EVT_BUTTON(ID_GO, FirstSetup::go)
wxEND_EVENT_TABLE()

FirstSetup::FirstSetup(const wxString& title, const wxString& this_paf)
    : wxFrame(nullptr, 69, title, wxDefaultPosition, wxDefaultSize)
{
    wxPanel* __p_pane = new wxPanel(this, 69);
    wxBoxSizer* __p_sizer = new wxBoxSizer(wxVERTICAL);
    __p_sizer->Add(__p_pane, 1, wxEXPAND);
    wxBoxSizer* p_sizer = new wxBoxSizer(wxVERTICAL);

    __choices[3] = {
        ("User Folder ( " + GV::consts::uPaf.string() + GV::consts::fsep + "uMgrData" + GV::consts::fsep + GV::consts::uName + GV::consts::fsep" )"),
        // a folder in user home dir
        ("App Local Folder ( " + this_paf + GV::consts::user_data_folder + GV::consts::fsep + GV::consts::uName + GV::consts::fsep" )"),
        // a folder in the place where the the app is
        // the option does not appear if the app is in the users dir
        "Other"
        // custom dir
    };

    if (this_paf.Find(GV::consts::uPaf.string()) == 0)
    {
        __choices[1] = __choices[2];
        len = 2;
    }

    // choice for the the pafs to store user's data
    paf_fr_data = new wxChoice(__p_pane, ID_CHOICES, wxDefaultPosition, wxDefaultSize, len, __choices);
    paf_fr_data->SetSelection(0);
    // browse files for folder
    browse_btn = new wxButton(__p_pane, ID_BROWSE, "Browse");

    wxBoxSizer* paf2choose = new wxBoxSizer(wxHORIZONTAL);
    paf2choose->Add(paf_fr_data, 1, wxEXPAND | wxALL, 5);
    paf2choose->Add(browse_btn, 0.5, wxEXPAND | wxALL, 5);
    browse_btn->Enable(false);
    // retsu chaji!!!!
    go_btn = new wxButton(__p_pane, ID_GO, "レツ　チャージ!");
    p_sizer->Add(paf2choose, 1, wxEXPAND | wxALL, 5);
    p_sizer->Add(go_btn, 0.5, wxALL | wxALIGN_RIGHT, 5);
    // pwd str
    wxStaticText* pwdtxt = new wxStaticText(__p_pane, 0, "Password:");
    p_sizer->Add(pwdtxt, 0.5, wxALL | wxEXPAND, 5);
    // pwd
    pwd = new wxTextCtrl(__p_pane, ID_PWD, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    p_sizer->Add(pwd, 0.5, wxALL | wxEXPAND, 5);
    // re-pwd str
    wxStaticText* pwdtxt2 = new wxStaticText(__p_pane, 0, "Re-enter Password:");
    p_sizer->Add(pwdtxt2, 0.5, wxALL | wxEXPAND, 0.5);
    // re-pwd
    re_pwd = new wxTextCtrl(__p_pane, ID_RE_PWD, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    p_sizer->Add(re_pwd, 0.5, wxALL | wxEXPAND, 5);

    __p_pane->SetSizerAndFit(p_sizer);
    this->SetSizerAndFit(__p_sizer);
}

void FirstSetup::choice(wxCommandEvent& evt)
{
    if (paf_fr_data->GetSelection() == len - 1)
    {
        browse_btn->Enable();
        return;
    }
    browse_btn->Enable(false);
}

void FirstSetup::go(wxCommandEvent& evt)
{
    std::ofstream file((GV::consts::c_app_data + GV::consts::fsep + "initialised.baka"));
    file.close();
    GV::consts::user_data_folder = std::string((__choices[paf_fr_data->GetSelection()].mb_str()));
    init();
    mainFrame* frm = new mainFrame("uMgr", wxDefaultPosition, wxDefaultSize);
    Show(false);
    frm->Show();
    Destroy();
}