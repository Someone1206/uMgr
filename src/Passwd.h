#pragma once
#include <wx/wx.h>
#include <fstream>

class Passwd
    : public wxFrame
{
public:
    Passwd(const wxString& title, std::ifstream& pwd_file);

private:
    std::ifstream* _pwd_file = nullptr;

    wxTextCtrl* pwd = nullptr;

    void _r_g(wxCommandEvent& evt);
    void canc__(wxCommandEvent& evt);
    void _f_pwd(wxCommandEvent& evt);

    ~Passwd();

    enum 
    {
        ID_B_RG,
        ID_CANC,
        ID_F_PWD,
        ID_PWD
    };
    wxDECLARE_EVENT_TABLE();
};

