#include "AddEntry.h"
#include "ufw/init.h"
#include "AddLog.h"

wxBEGIN_EVENT_TABLE(AddEntry, wxFrame)
    EVT_BUTTON(ID_ADD, AddEntry::addEntry)
    EVT_BUTTON(ID_ADDE_N_L, AddEntry::addEntry_n_log)
    EVT_BUTTON(ID_CANCEL, AddEntry::cancel)
wxEND_EVENT_TABLE()

AddEntry::AddEntry(wxWindow* parent, const wxString& title, const wxPoint& pos, const wxString& genre, bool _idk)
    :
    wxFrame(parent, 69, title, pos, wxDefaultSize, wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT) {
    // disable the parent
    this->GetParent()->Enable(false);
    gen_name = genre;
    idk = _idk;

    // the topmost panel, no other way
    wxPanel* __p_pane = new wxPanel(this, 69);
    wxBoxSizer* __p_pane_sizer = new wxBoxSizer(wxVERTICAL); // sizer for toplevel panel
    __p_pane_sizer->Add(__p_pane, 1, wxEXPAND);
    // actual parent sizer for every other crap
    wxBoxSizer* p_sizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* sheesh = new wxStaticText(__p_pane, 69, ("Add Entry for genre " + genre)); // don't mess here if you are having amnesia
    {
        wxFont sheesh_font(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        sheesh->SetFont(sheesh_font);
    }
    entry_name = new wxTextCtrl(__p_pane, ID_ENTRY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTER);

    // all crap buttons
    wxButton* btn_ok = new wxButton(__p_pane, ID_ADD, "Okay Add");
    wxButton* btn_okN_en = new wxButton(__p_pane, ID_ADDE_N_L, "Add Entry & Log");
    wxButton* btn_cancel = new wxButton(__p_pane, ID_CANCEL, "Cancel");

    // sizer for buttons
    wxBoxSizer* btn_sizer = new wxBoxSizer(wxHORIZONTAL);
    btn_sizer->Add(btn_cancel, wxEXPAND | wxALL, 15);
    btn_sizer->Add(btn_okN_en, wxEXPAND | wxALL, 15);
    btn_sizer->Add(btn_ok, wxEXPAND | wxALL, 15);

    // add crap to the parent sizer
    p_sizer->Add(sheesh, 0.1, wxEXPAND | wxLEFT | wxTOP, 15);
    p_sizer->Add(entry_name, 1, wxEXPAND | wxALL, 8);
    p_sizer->Add(btn_sizer, 0.1, wxALL | wxALIGN_RIGHT, 9);

    // don't mess here if you are having amnesia xactly like me
    __p_pane->SetSizerAndFit(p_sizer);

    this->SetSizerAndFit(__p_pane_sizer);
}

void AddEntry::addEntry(wxCommandEvent& evt)
{
    if (createEntry(entry_name->GetValue(), gen_name)) {
        this->Destroy();
        Destroy();
    }
}

void AddEntry::addEntry_n_log(wxCommandEvent& evt)
{
    std::string format = "";
    {
        std::ifstream formatF((GV::consts::user_data_folder + FSEP + std::string(gen_name.mb_str()) + FSEP + "format.hentai"));
        getline(formatF, format);
    }
    if (createEntry(entry_name->GetValue(), gen_name)) {
        ReadOptions option;
        if (format == "Anime" || format == "Hentai")
            option = Anime;
        else if (format == "Manga")
            option = Manga;
        else if (format == "Movies")
            option = Movies;
        else
            option = Others;
        AddLog* addLog = new AddLog(this, ("Add log for " + entry_name->GetValue() + " in genre " + gen_name),
            option, entry_name->GetValue(), wxPoint(this->GetPosition().x + 20, this->GetPosition().y + 20), 
            wxDefaultSize, 
            (GV::consts::user_data_folder + FSEP + gen_name + FSEP + entry_name->GetValue() + ".baka"));
        addLog->Show();
    }
}

void AddEntry::cancel(wxCommandEvent& evt)
{
    Destroy();
}

AddEntry::~AddEntry()
{
    if (idk)
        this->GetParent()->Destroy();
    this->GetParent()->Enable();
}

