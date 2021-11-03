#include "FirstSetup.h"
#include "ufw/fileIO.h"
#include "mainFrame.h"

wxBEGIN_EVENT_TABLE(FirstSetup, wxFrame)
    EVT_CHOICE(PAF_CHOICES, FirstSetup::choice)
    EVT_BUTTON(BTN_BROWSE, FirstSetup::browse)
    EVT_BUTTON(ID_GO, FirstSetup::go)
    EVT_BUTTON(ID_CANCEL, FirstSetup::cancel)
    EVT_CHECKBOX(ADD_PWD, FirstSetup::a_pwd)
wxEND_EVENT_TABLE()

FirstSetup::FirstSetup(const wxString& thisPaf)
    :wxFrame(nullptr, wxID_ANY, "First Setup", wxPoint(), wxSize(), wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
    wxPanel* __p_pane = new wxPanel(this, 69); // the main parent panel
    
    // the main parent sizer, only holds __p_pane
    wxBoxSizer* __p_sizer = new wxBoxSizer(wxVERTICAL);
    __p_sizer->Add(__p_pane, 1, wxEXPAND);

    wxBoxSizer* p_sizer = new wxBoxSizer(wxVERTICAL);
    // the parent sizer for all other stuffs.

    __choices[0] = ("Your User Folder: (" + uFolder);
    __choices[1] = ("In App Folder: (" + thisPaf + FSEP + folderN + FSEP);
    __choices[2] = "Browse";
    // the choices

    if (thisPaf.Find(GV::consts::uPaf.string()) == 0) {
        len = 2;
        __choices[1] = __choices[2];
        // the app folder is not needed if the exe is in the 
        // user's home folder
    }

    // static text for the (uhhh...)
    wxStaticText* f_setup = new wxStaticText(__p_pane, 69, "First Setup", wxPoint(), wxSize(), wxALIGN_CENTRE_HORIZONTAL);
    {
        wxFont f_s_f(35, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD); // ff_script, decor
        f_s_f.MakeBold();
        f_setup->SetFont(f_s_f);
    }
    p_sizer->Add(f_setup, 1, wxALIGN_CENTER, 5); // add the text to the parent sizer

    // text ctrl to show some details
    details = new wxTextCtrl(__p_pane, DET_TXT_CTRL, str_in_uPaf, wxPoint(), wxSize(),
        wxTE_MULTILINE | wxTE_READONLY | wxTE_CENTRE | wxTE_BESTWRAP
    );
    p_sizer->Add(details, 1, wxALL, 7); // add it to the parent sizer

    // the text ctrl to show the path selected
    __paf_sel = new wxTextCtrl(__p_pane, PAF_TXT_CTRL, ("Path Selected:   " + uFolder), wxPoint(), wxSize(), wxTE_READONLY);
    p_sizer->Add(__paf_sel, 0.5, wxEXPAND | wxALL, 5);


    // choice for paths
    paf_fr_data = new wxChoice(__p_pane, PAF_CHOICES, wxPoint(), wxSize(), len, __choices);
    paf_fr_data->SetSelection(0);

    // browse folder for folder to store logs and data
    browse_btn = new wxButton(__p_pane, BTN_BROWSE, "Browse");

    // sizer for paf choice and browse btn
    wxBoxSizer* paf_choice = new wxBoxSizer(wxHORIZONTAL);
    paf_choice->Add(paf_fr_data, 1, wxALL, 5);
    paf_choice->Add(browse_btn, 0.5, wxALL, 5);
    browse_btn->Enable(false);

    p_sizer->Add(paf_choice, 0.2, wxEXPAND | wxALL, 5);

    // checkbox. check if you wanna add password
    wxCheckBox* add_pwd$ = new wxCheckBox(__p_pane, ADD_PWD, " Add Password?");
    add_pwd$->SetValue(true); // yes add password is default
    p_sizer->Add(add_pwd$, 0.5, wxALL, 5);


    // password stuffs
    // controls needed for password input
    wxStaticText* pwd_txt = new wxStaticText(__p_pane, 69, "Password:");
    pwd = new wxTextCtrl(__p_pane, ID_PWD, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    wxStaticText* re_pwd_txt = new wxStaticText(__p_pane, 69, "Re-enter Password:");
    re_pwd = new wxTextCtrl(__p_pane, ID_RE_PWD, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);

    p_sizer->Add(pwd_txt, 0.5, wxALL, 5);
    p_sizer->Add(pwd, 0.5, wxEXPAND | wxALL, 5);
    p_sizer->Add(re_pwd_txt, 0.5, wxALL, 5);
    p_sizer->Add(re_pwd, 0.5, wxEXPAND | wxALL, 5);

    // corner button sizer
    wxBoxSizer* btn_sizer = new wxBoxSizer(wxHORIZONTAL);
    // retsu chaji!!!!    
    wxButton* go_btn = new wxButton(__p_pane, ID_GO, "レツ　チャージ!");
    // cancel wt...?!?
    wxButton* cancel_ = new wxButton(__p_pane, ID_CANCEL, "cancel -_-?");
    btn_sizer->Add(cancel_, 0.5, wxALL, 5);
    btn_sizer->Add(go_btn, 0.5, wxALL, 5);
    p_sizer->Add(btn_sizer, 0.5, wxALIGN_RIGHT | wxALL, 5);
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
            __paf_sel->SetValue("No Path Selected!");
            details->SetValue(("I don't recommend using any other folder other than your"
                "\nuser folder as it is vulnerable to intruders."));
        }
        else
            __paf_sel->SetValue(("Other:  " + paf_selected));
        browse_btn->Enable();
        return;
    }
    else
    {
        uFolder = GV::consts::uPaf.string() + FSEP + folderN + FSEP;
        details->SetValue(str_in_uPaf);
        // setting the path to exe folder if index is not 0
        if (paf_fr_data->GetSelection() != 0)
        {
            do_smth = true;
            uFolder = std::string(_this_paf.mb_str()) + FSEP + folderN + FSEP + GV::consts::uName;
            details->SetValue((tmp + uFolder + "\n"
                "( That's vulnerable to 侵入者! But I'll try my best to keep your privacy)"));
        }
        __paf_sel->SetLabel("Path Selected:  " + uFolder);
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
    pwd->Enable(uhh);
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
        uFolder = paf_selected;
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
                " or just simply type a password you can remember", "マジで！？", wxOK | wxICON_ERROR);
            return;
        }
        std::string __passwd = std::string(passwd.mb_str());
        if (isspace(__passwd))
            wxMessageBox("Warning: Password contains only spaces\\tabs.", "Uhh Ok!", wxOK | wxICON_WARNING);
        __a_pwd = 1;
    }
    else if (std::filesystem::exists((aFolder + FSEP + "pwd.hentai")))
        std::filesystem::remove((aFolder + FSEP + "pwd.hentai"));

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

    std::ofstream file((aFolder + FSEP + "initialised.baka"));
    file.close();

    if (__a_pwd)
    {
        file.open((aFolder + FSEP + "pwd.hentai"));
        file << std::string(pwd->GetValue().mb_str());
        file.close();
    }

    file.open((aFolder + FSEP + "pafs.hentai"));
    file << uFolder;
    file.close();

    std::filesystem::create_directories(uFolder);

    if (do_smth && std::filesystem::exists(uFolder))
        std::filesystem::permissions(uFolder,
            std::filesystem::perms::owner_all,
            std::filesystem::perm_options::add);

    mainFrame* main_frame = new mainFrame("kill me", wxDefaultPosition, wxDefaultSize);
    this->Show(false);
    main_frame->Show();

    Destroy();
}

void FirstSetup::cancel(wxCommandEvent& evt)
{
    Destroy();
}