#include "Passwd.h"
#include "mainFrame.h"
#include "ufw/GV.h"
#include "ufw/init.h"

wxBEGIN_EVENT_TABLE(Passwd,wxFrame)
    EVT_BUTTON(ID_B_RG, Passwd::_r_g)
    EVT_BUTTON(ID_CANC, Passwd::canc__)
    EVT_BUTTON(ID_F_PWD, Passwd::_f_pwd)
wxEND_EVENT_TABLE()


Passwd::Passwd(const wxString& title)
    :wxFrame(nullptr, 69, title, wxDefaultPosition, wxDefaultSize, wxCAPTION | wxMINIMIZE_BOX
        | wxCLOSE_BOX | wxSYSTEM_MENU)
{
    wxPanel* __p_pane = new wxPanel(this);
    wxBoxSizer* _p__s = new wxBoxSizer(wxVERTICAL);
    _p__s->Add(__p_pane, wxEXPAND);
    wxBoxSizer* p_sizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* pwd_disp = new wxStaticText(__p_pane, 69, "Password");
    {
        wxFont idk(25, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_MAX, wxFONTWEIGHT_EXTRABOLD);
        pwd_disp->SetFont(idk);
    }
    p_sizer->Add(pwd_disp, 0.5, wxALL, 5);

    pwd = new wxTextCtrl(__p_pane, ID_PWD, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    p_sizer->Add(pwd, 0.2, wxEXPAND | wxALL, 10);

    wxBoxSizer* btn_s = new wxBoxSizer(wxHORIZONTAL);

    wxButton* レツゴ = new wxButton(__p_pane, ID_B_RG, "レツゴ～");     // :>
    wxButton* canc = new wxButton(__p_pane, ID_CANC, "Cancel -_-?");
    // wxButton* f_pwd = new wxButton(__p_pane, ID_F_PWD, "Forgot Password"); later

    btn_s->Add(レツゴ, 0.5, wxALL, 5);    // :>
    btn_s->Add(canc, 0.5, wxALL, 5);
    // btn_s->Add(f_pwd, 0.5, wxALL, 5);

    p_sizer->Add(btn_s, 0.3, wxALL | wxALIGN_RIGHT, 5);

    __p_pane->SetSizerAndFit(p_sizer);
    this->SetSizerAndFit(_p__s);
}

void Passwd::_r_g(wxCommandEvent& evt)
{
    wxString pwd_ff;
    {
        std::ifstream pwd_file((aFolder + FSEP + "pwd.hentai"));
        std::string tmp;
        getline(pwd_file, tmp);
        pwd_ff = tmp;
    }

    if (pwd_ff != pwd->GetValue())
    {
        wxMessageBox("!!!  Password doesn't match   !!!");
        return;
    }
    
    mainFrame* uhh = new mainFrame(getFrameTitle(), wxDefaultPosition, wxDefaultSize); // cuztom title :>
    this->Show(false);
    uhh->Show();
    Destroy();
}

void Passwd::canc__(wxCommandEvent& evt)
{
    Destroy();
}

// will never do it...
void Passwd::_f_pwd(wxCommandEvent& evt)
{
}

Passwd::~Passwd()
{
    // idk do whatever
}