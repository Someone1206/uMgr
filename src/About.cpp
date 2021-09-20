#include "About.h"

wxBEGIN_EVENT_TABLE(About, wxFrame)
    EVT_BUTTON(ID_OK_BTN, About::okei)
wxEND_EVENT_TABLE()

About::About(wxWindow* frame, const wxPoint& pos, const wxSize& size, wxColor* theme)
    :
    wxFrame(frame, 69, "About", pos, size) {
    
    wxPanel* m_panel = new wxPanel(this, ID_PANEL, wxDefaultPosition);
    m_panel->SetBackgroundColour(*theme);
    
    wxBoxSizer* iCantNameIt = new wxBoxSizer(wxVERTICAL);
    iCantNameIt->Add(m_panel, 2, wxEXPAND);
    iCantNameIt->SetMinSize(wxSize(300, 220));

    wxBoxSizer* m_sizer = new wxBoxSizer(wxVERTICAL);

    //abt = new wxStaticText(m_panel, 69, "Watching Hentai");
    wxString aboutS = "Watching Hentai";


    wxTextCtrl* abt = new wxTextCtrl(m_panel, 69, aboutS, wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE);
    okBtn = new wxButton(m_panel, ID_OK_BTN, "Okay");
    m_sizer->Add(abt, 1, wxEXPAND | wxALL, 5);

    wxBoxSizer* c_sizer = new wxBoxSizer(wxHORIZONTAL);
    c_sizer->Add(okBtn, 0, wxRIGHT, 10);

    m_sizer->Add(c_sizer, 0, wxALIGN_RIGHT | wxBOTTOM | wxRIGHT, 5);
    m_panel->SetSizerAndFit(m_sizer);

    this->SetSizerAndFit(iCantNameIt);
}

void About::okei(wxCommandEvent& evt)
{
    Destroy();
}

About::~About()
{
    //
}
