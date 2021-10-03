#include "FirstSetup.h"
wxBEGIN_EVENT_TABLE(FirstSetup, wxFrame)
    EVT_CHOICE(ID_CHOICES, FirstSetup::choice)
    EVT_BUTTON(ID_GO, FirstSetup::go)
wxEND_EVENT_TABLE()

FirstSetup::FirstSetup(const wxString& title, const wxString& this_paf)
    : wxFrame(nullptr, 69, title, wxDefaultPosition, wxDefaultSize)
{
    // gobergardens
    wxPanel* __p_pane = new wxPanel(this, 69);
    wxBoxSizer* __p_sizer = new wxBoxSizer(wxVERTICAL);
    __p_sizer->Add(__p_pane, 1, wxEXPAND);
    wxBoxSizer* p_sizer = new wxBoxSizer(wxVERTICAL);

    wxString __choices[3] = {
        ("User Folder ( " + GV::consts::uPaf.string() + GV::consts::fsep + GV::consts::uName + " )"),
        ("App Local Folder ( " + this_paf + GV::consts::fsep + GV::consts::uName + " )"),
        "Other"
    };
    int fck;
    if ((fck = this_paf.Find(GV::consts::uPaf.string())) == 0)
    {
        wxMessageBox(GV::consts::uPaf.string(), "debugx1100");
        __choices[1] = __choices[2];
        len = 2;
    }

    paf_fr_data = new wxChoice(__p_pane, ID_CHOICES, wxDefaultPosition, wxDefaultSize, len, __choices);
    paf_fr_data->SetSelection(0);

    browse_btn = new wxButton(__p_pane, ID_BROWSE, "Browse");

    wxBoxSizer* paf2choose = new wxBoxSizer(wxHORIZONTAL);
    paf2choose->Add(paf_fr_data, 1, wxEXPAND | wxALL, 5);
    paf2choose->Add(browse_btn, 0.5, wxEXPAND | wxALL, 5);
    browse_btn->Enable(false);

    go_btn = new wxButton(__p_pane, ID_GO, "Go!");

    p_sizer->Add(paf2choose, 1, wxEXPAND | wxALL, 5);
    p_sizer->Add(go_btn, 0.5, wxALL | wxALIGN_RIGHT, 5);

    __p_pane->SetSizerAndFit(p_sizer);
    this->SetSizerAndFit(__p_sizer);
}

void FirstSetup::choice(wxCommandEvent& evt)
{
    if (paf_fr_data->GetSelection() == len - 1)
    {
        browse_btn->Enable();
        wxMessageBox("Button Hidden");
        return;
    }
    browse_btn->Enable(false);
}

void FirstSetup::go(wxCommandEvent& evt)
{
    Destroy();
}