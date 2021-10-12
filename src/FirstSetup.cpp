#include "FirstSetup.h"
#include "mainFrame.h"
#include "ufw/GV.h"
#include "ufw/init.h"

wxBEGIN_EVENT_TABLE(FirstSetup, wxFrame)
    EVT_CHOICE(ID_CHOICES, FirstSetup::choice)
    EVT_BUTTON(ID_BROWSE, FirstSetup::browse)
    EVT_BUTTON(ID_GO, FirstSetup::go)
    EVT_BUTTON(ID_CANC, FirstSetup::cancel)
    EVT_CHECKBOX(ID_A_PWD_, FirstSetup::a_pwd)
wxEND_EVENT_TABLE()

FirstSetup::FirstSetup(const wxString& title, const wxString& this_paf)
    : wxFrame(nullptr, 69, title, wxDefaultPosition, wxDefaultSize, wxCAPTION | wxMINIMIZE_BOX 
        | wxCLOSE_BOX | wxSYSTEM_MENU)
    // it ain't resizable
{
    _this_paf = this_paf;
    GV::consts::user_data_folder = GV::consts::uPaf.string() + FSEP + folderN + FSEP;

    wxPanel* __p_pane = new wxPanel(this, 69);
    // main sizer only holds panel
    wxBoxSizer* __p_sizer = new wxBoxSizer(wxVERTICAL);
    __p_sizer->Add(__p_pane, 1, wxEXPAND);
    //
    // parent sizer, held by the panel, holds other stuffs
    wxBoxSizer* p_sizer = new wxBoxSizer(wxVERTICAL);

    // choices to store the user's data 
    __choices[0] = ("In Your User Folder (" + GV::consts::uPaf.string() + FSEP + folderN + FSEP + ")");
    // path is defaulted in the user folder
    __choices[1] = ("In App Folder (" + this_paf + FSEP + folderN + FSEP + GV::consts::uName + FSEP+ ")");
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
    {
        wxFont idk(35, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD); // ff_script, decor
        idk.MakeBold();
        setup->SetFont(idk);
    }
    p_sizer->Add(setup, 1, wxALIGN_CENTER, 5);
    details = new wxStaticText(__p_pane, 69, ("Your logs will be stored in the following directory:\n"
        "" + GV::consts::user_data_folder + ""
        "\nThis is the recommended path since your logs will be safe from intruders\n (other "
        "users on your OS) via the filesystem\n")
    );
    {
        wxFont idk(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        idk.MakeBold();
        details->SetFont(idk);
    }
    p_sizer->Add(details, 1, wxALL, 7);
    // shows the path selected
    __paf_sel = new wxStaticText(__p_pane, 69, ("Path Selected:  " + GV::consts::user_data_folder));
    {
        wxFont idk(9, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRAHEAVY);
        __paf_sel->SetFont(idk);
    }
    p_sizer->Add(__paf_sel, 0.5, wxEXPAND | wxALL, 5);


    // choice for the the pafs to store user's data
    paf_fr_data = new wxChoice(__p_pane, ID_CHOICES, wxDefaultPosition, wxDefaultSize, len, __choices);
    paf_fr_data->SetSelection(0);
    
    // browse files for folder
    browse_btn = new wxButton(__p_pane, ID_BROWSE, "Browse");
    
    // sizer for paf choice and browse btn
    wxBoxSizer* paf2choose = new wxBoxSizer(wxHORIZONTAL);
    paf2choose->Add(paf_fr_data, 1, wxALL, 5);
    paf2choose->Add(browse_btn, 0.5, wxALL, 5);
    browse_btn->Enable(false);
    
    p_sizer->Add(paf2choose, 0.2, wxEXPAND | wxALL, 5);

    wxCheckBox* add_pwd = new wxCheckBox(__p_pane, ID_A_PWD_, "Add Password?");
    add_pwd->SetValue(true);
    p_sizer->Add(add_pwd, 0.5, wxALL, 5);

    // pwd str
    pwdtxt = new wxStaticText(__p_pane, 0, "Password:");
    p_sizer->Add(pwdtxt, 0.5, wxALL, 5);
    // pwd
    pwd = new wxTextCtrl(__p_pane, ID_PWD, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    p_sizer->Add(pwd, 0.5, wxEXPAND | wxALL, 5);
    // re-pwd str
    pwdtxt2 = new wxStaticText(__p_pane, 0, "Re-enter Password:");
    p_sizer->Add(pwdtxt2, 0.5, wxALL, 5);
    // re-pwd
    re_pwd = new wxTextCtrl(__p_pane, ID_RE_PWD, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    p_sizer->Add(re_pwd, 0.5, wxALL | wxEXPAND, 5);



    wxBoxSizer* btn_s = new wxBoxSizer(wxHORIZONTAL);
    // retsu chaji!!!!    
    go_btn = new wxButton(__p_pane, ID_GO, "レツ　チャージ!");
    // cancel wt...?!?
    cancel_ = new wxButton(__p_pane, ID_CANC, "cancel -_-?");
    btn_s->Add(cancel_, 0.5, wxALL, 5);
    btn_s->Add(go_btn, 0.5, wxALL, 5);
    p_sizer->Add(btn_s, 0.5, wxALIGN_RIGHT | wxALL, 5);
    go_btn->SetFocus();

    __p_pane->SetSizerAndFit(p_sizer);
    this->SetSizerAndFit(__p_sizer);
}

void FirstSetup::choice(wxCommandEvent& evt)
{
    std::string tmp = "Your logs will be stored in the following directory:\n";
    if (paf_fr_data->GetSelection() == len - 1)
    {
        if (paf_selected == "")
        {
            __paf_sel->SetLabel("No Path Selected!");
            details->SetLabel(("I don't recommend using any other folder other than your"
                "\nuser folder as it is vulnerable to intruders."));
        }
        else
            __paf_sel->SetLabel(("Other:  " + paf_selected));
        browse_btn->Enable();
        return;
    }
    else
    {
        GV::consts::user_data_folder = GV::consts::uPaf.string() + FSEP + folderN + FSEP;
        details->SetLabel((tmp + GV::consts::user_data_folder + "\n"
            "\nThis is the recommended path since your logs will be safe from 侵入者\n(other "
            "users on your OS) via the filesystem\n"));
        // setting the path to exe folder if index is not 0
        if (paf_fr_data->GetSelection() != 0)
        {
            do_smth = true;
            GV::consts::user_data_folder = std::string(_this_paf.mb_str()) + FSEP + folderN + FSEP + GV::consts::uName;
            details->SetLabel((tmp + GV::consts::user_data_folder + "\n"
                "( That's vulnerable to 侵入者! But I'll try my best to keep your privacy)"));
        }
        __paf_sel->SetLabel("Path Selected:  " + GV::consts::user_data_folder);
    }
    browse_btn->Enable(false);
}

void FirstSetup::browse(wxCommandEvent& evt)
{
    std::string tmp = "Your logs will be stored in the following directory:\n";
    wxDirDialog dlg(nullptr, "Choose Folder to store your Logs!", "",
        wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST
        );
    dlg.ShowModal();
    paf_selected = dlg.GetPath();
    
    if (paf_selected.Find(GV::consts::uPaf.string()) == 0)
        details->SetLabel((tmp + paf_selected + "\n"
            "(it's good. You probably will be safe from 侵入者)"));
    else
    {
        do_smth = true;
        details->SetLabel((tmp + paf_selected + "\n"
            "( That's vulnerable to 侵入者! But I'll try my best to keep your privacy)"));
    }
    __paf_sel->SetLabel("Path Selected:   " + paf_selected);
}

void FirstSetup::a_pwd(wxCommandEvent& evt)
{
    bool uhh = evt.IsChecked();
    pwdtxt->Enable(uhh);
    pwd->Enable(uhh);
    pwdtxt2->Enable(uhh);
    re_pwd->Enable(uhh);
}

void FirstSetup::go(wxCommandEvent& evt)
{
    if (paf_fr_data->GetSelection() == len - 1)
    {
        std::string tmp = std::string(paf_selected.mb_str());
        if (isspace(tmp))
        {
            wxMessageBox("No folder selected!");
            return;
        }
        GV::consts::user_data_folder = paf_selected;
    }

    bool __a_pwd = 0;

    if (pwd->IsEnabled())
    {
        wxString passwd = pwd->GetValue();
        if (passwd != re_pwd->GetValue())
        {
            wxMessageBox("!!!!!  Passwords Don't Match  !!!!!", "ばかが？", wxOK | wxICON_ERROR);
            return;
        }
        else if (passwd == "")
        {
            wxMessageBox("Password is empty -_-. Please uncheck \"Add Password?\" checkbox to not add password"
                " or just simply type a password you can remember", "マジで！", wxOK | wxICON_ERROR);
            return;
        }
        std::string __passwd = std::string(passwd.mb_str());
        if (isspace(__passwd))
            wxMessageBox("Warning: Password contains only spaces\\tabs.", "Uhh Ok!", wxOK | wxICON_WARNING);
        __a_pwd = 1;
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

    if (__a_pwd)
    {
        file.open((GV::consts::c_app_data + FSEP + "pwd.hentai"));
        file << std::string(pwd->GetValue().mb_str());
        file.close();
    }

    file.open((GV::consts::c_app_data + FSEP + "pafs.hentai"));
    file << GV::consts::user_data_folder;
    file.close();

    std::filesystem::create_directories(GV::consts::user_data_folder);

    if (do_smth && std::filesystem::exists(GV::consts::user_data_folder))
        std::filesystem::permissions(GV::consts::user_data_folder,
            std::filesystem::perms::owner_all,
            std::filesystem::perm_options::add);
    
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
