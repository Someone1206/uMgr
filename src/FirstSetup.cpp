#include "FirstSetup.h"
#include "mainFrame.h"
#include "ufw/GV.h"
#include "ufw/init.h"

wxBEGIN_EVENT_TABLE(FirstSetup, wxFrame)
    EVT_CHOICE(ID_CHOICES, FirstSetup::choice)
    EVT_BUTTON(ID_BROWSE, FirstSetup::browse)
    EVT_BUTTON(ID_GO, FirstSetup::go)
    EVT_BUTTON(ID_CANC, FirstSetup::cancel)
wxEND_EVENT_TABLE()

FirstSetup::FirstSetup(const wxString& title, const wxString& this_paf, bool& init)
    : wxFrame(nullptr, 69, title, wxDefaultPosition, wxDefaultSize, wxCAPTION | wxMINIMIZE_BOX 
        | wxCLOSE_BOX | wxSYSTEM_MENU)
    // it ain't resizable
{
    _this_paf = this_paf;
    __init = &init;
    GV::consts::user_data_folder = GV::consts::uPaf.string() + FSEP + "uMgrData" + FSEP;

    wxPanel* __p_pane = new wxPanel(this, 69);
    // main sizer only holds panel
    wxBoxSizer* __p_sizer = new wxBoxSizer(wxVERTICAL);
    __p_sizer->Add(__p_pane, 1, wxEXPAND);
    //
    // parent sizer, held by the panel, holds other stuffs
    wxBoxSizer* p_sizer = new wxBoxSizer(wxVERTICAL);

    // choices to store the user's data 
    __choices[0] = ("In Your User Folder (" + GV::consts::uPaf.string() + FSEP + "uMgrData" + FSEP + ")");
    // path is defaulted in the user folder
    __choices[1] = ("In App Folder (" + this_paf + FSEP + "uMgrData" + FSEP + GV::consts::uName + FSEP+ ")");
    // the local folder of the exe/bin
    __choices[2] = "Other";
    // other paf

    // if the exe is in the user's home dir
    if (this_paf.Find(GV::consts::uPaf.string()) == 0)
    {
        // 2nd option => others
        __choices[1] = __choices[2];
        // options to show in the dropdown
        len = 2;
    }

    wxStaticText* setup = new wxStaticText(__p_pane, 69, "Initial Setup");
    p_sizer->Add(setup, 1, wxEXPAND | wxALL, 5);
    details = new wxStaticText(__p_pane, 69, det_str);
    p_sizer->Add(details, 1, wxEXPAND | wxALL, 5);
    // shows the path selected
    __paf_sel = new wxStaticText(__p_pane, 69, ("Path Selected:  " + GV::consts::user_data_folder));
    p_sizer->Add(__paf_sel, 0.5, wxEXPAND | wxALL, 5);


    // choice for the the pafs to store user's data
    paf_fr_data = new wxChoice(__p_pane, ID_CHOICES, wxDefaultPosition, wxDefaultSize, len, __choices);
    paf_fr_data->SetSelection(0);
    
    // browse files for folder
    browse_btn = new wxButton(__p_pane, ID_BROWSE, "Browse");
    
    // sizer for paf choice and browse btn
    wxBoxSizer* paf2choose = new wxBoxSizer(wxHORIZONTAL);
    paf2choose->Add(paf_fr_data, 1, wxEXPAND | wxALL, 5);
    paf2choose->Add(browse_btn, 0.5, wxEXPAND | wxALL, 5);
    browse_btn->Enable(false);
    
    p_sizer->Add(paf2choose, 1, wxEXPAND | wxALL, 5);
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



    // retsu chaji!!!!    
    go_btn = new wxButton(__p_pane, ID_GO, "レツ　チャージ!");
    p_sizer->Add(go_btn, 0.5, wxALL | wxALIGN_RIGHT, 5);
    // cancel wt...?!?
    cancel_ = new wxButton(__p_pane, ID_CANC, "cancel -_-?");
    p_sizer->Add(cancel_, 0.5, wxALL | wxALIGN_RIGHT, 5);


    __p_pane->SetSizerAndFit(p_sizer);
    this->SetSizerAndFit(__p_sizer);
}

void FirstSetup::choice(wxCommandEvent& evt)
{
    if (paf_fr_data->GetSelection() == len - 1)
    {
        if (paf_selected == "")
            __paf_sel->SetLabel("No Path Selected!");
        else
            __paf_sel->SetLabel(("Other:  " + paf_selected));
        browse_btn->Enable();
        return;
    }
    else
    {
        GV::consts::user_data_folder = GV::consts::uPaf.string() + FSEP + "uMgrData" + FSEP;
        // setting the path to exe folder if index is not 0
        if (paf_fr_data->GetSelection() != 0)
        {
            GV::consts::user_data_folder = std::string(_this_paf.mb_str()) + FSEP + "uMgrData" + FSEP + GV::consts::uName;
        }
        __paf_sel->SetLabel("Path Selected:  " + GV::consts::user_data_folder);
    }
    browse_btn->Enable(false);
}

void FirstSetup::browse(wxCommandEvent& evt)
{
    wxDirDialog dlg(nullptr, "Choose Folder to store your Logs!", "",
        wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST
        );
    dlg.ShowModal();
    paf_selected = dlg.GetPath();
    __paf_sel->SetLabel("Path Selected:   " + paf_selected);
}

void FirstSetup::go(wxCommandEvent& evt)
{
    if (pwd->GetValue() != re_pwd->GetValue())
    {
        wxMessageBox("!!!!!  Passwords Don't Match  !!!!!", "ばかが？", wxOK | wxICON_ERROR);
        return;
    }
#if _WIN32
    {
        std::wstring tmp(GV::consts::c_app_data.begin(), GV::consts::c_app_data.end());
        LPCWSTR irdk = tmp.c_str();
        CreateDirectory(irdk, nullptr);
        SetFileAttributes(irdk, FILE_ATTRIBUTE_HIDDEN);
    }
#else
    mkdir(GV::consts::c_app_data);
#endif // _WIN32

    std::ofstream file((GV::consts::c_app_data + FSEP + "initialised.baka"));
    file.close();


    {
        std::string tmp = std::string(paf_selected.mb_str());
        if (isspace(tmp) && paf_fr_data->GetSelection() == len - 1)
        {
            if (isspace(tmp))
            {
                wxMessageBox("No folder selected!");
                return;
            }
            GV::consts::user_data_folder = paf_selected;
        }
    }

    file.open((GV::consts::c_app_data + FSEP + "pafs.hentai"));
    file << GV::consts::user_data_folder;
    file.close();
    
    // init(set);
    // mainFrame* frm = new mainFrame("uMgr", wxDefaultPosition, wxDefaultSize);
    // Show(false);
    // frm->Show();

    // delete _this_paf;

    Destroy();
}

void FirstSetup::cancel(wxCommandEvent& evt)
{
    Destroy();
}
