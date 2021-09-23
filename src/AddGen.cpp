#include "AddGen.h"
#include "AddEntry.h"
#include "ufw/init.h"

wxBEGIN_EVENT_TABLE(AddGen, wxFrame)
    EVT_BUTTON(ID_ADD, AddGen::addGen)
    EVT_BUTTON(ID_ADDG_N_E, AddGen::addGenN_entry)
    EVT_BUTTON(ID_CANCEL, AddGen::cancel)
wxEND_EVENT_TABLE()


AddGen::AddGen(wxWindow* frame, const wxString& title, const wxPoint& pos, const wxSize& size)
    :
    wxFrame(frame, 69, title, pos, size, wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT) {
    // disable the parent
    this->GetParent()->Enable(false);
    // the topmost panel, no other way
    wxPanel* __p_pane = new wxPanel(this, 69);
    wxBoxSizer* __p_pane_sizer = new wxBoxSizer(wxVERTICAL); // sizer for toplevel panel
    __p_pane_sizer->Add(__p_pane, 1, wxEXPAND);
    // actual parent sizer for every other crap
    wxBoxSizer* p_sizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* sheesh = new wxStaticText(__p_pane, 69, "&Add Genre"); // don't mess here if you are having amnesia
    {
        wxFont sheesh_font(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        sheesh->SetFont(sheesh_font);
    }
    gen_name = new wxTextCtrl(__p_pane, ID_GENN, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTER);

    // all crap buttons
    wxButton* btn_ok = new wxButton(__p_pane, ID_ADD, "Okay Add");
    wxButton* btn_okN_en = new wxButton(__p_pane, ID_ADDG_N_E, "Add Genre & Entry");
    wxButton* btn_cancel = new wxButton(__p_pane, ID_CANCEL, "Cancel");

    // sizer for buttons
    wxBoxSizer* btn_sizer = new wxBoxSizer(wxHORIZONTAL);
    btn_sizer->Add(btn_cancel, wxEXPAND | wxALL, 15);
    btn_sizer->Add(btn_okN_en, wxEXPAND | wxALL, 15);
    btn_sizer->Add(btn_ok, wxEXPAND | wxALL, 15);

    // add crap to the parent sizer
    p_sizer->Add(sheesh, 0.1, wxEXPAND | wxLEFT | wxTOP, 15);
    p_sizer->Add(gen_name, 1, wxEXPAND | wxALL, 8);
    p_sizer->Add(btn_sizer, 0.1, wxALL | wxALIGN_RIGHT, 9);

    // don't mess here if you are having amnesia xactly like me
    __p_pane->SetSizerAndFit(p_sizer);

    this->SetSizerAndFit(__p_pane_sizer);
}

void AddGen::addGen(wxCommandEvent& evt) {
    
    if (createGen(gen_name->GetValue()))
        Destroy();
    return;
}

void AddGen::addGenN_entry(wxCommandEvent& evt) {
    if (createGen(gen_name->GetValue())) {
        AddEntry* fook = new AddEntry(this,
            ("Add Entry for " + gen_name->GetValue()), 
            wxPoint(this->GetPosition().x + 20, this->GetPosition().y + 20),
            gen_name->GetValue());
        fook->Show();
    }
}

void AddGen::cancel(wxCommandEvent& evt) {
    Destroy();
}

AddGen::~AddGen()
{
    // re-enabling the parent window
    this->GetParent()->Enable();
}
