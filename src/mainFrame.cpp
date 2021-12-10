#include "mainFrame.h"

mainFrame::mainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    :wxFrame(nullptr, 69, title, pos, size)
{
    __p_pane = new wxPanel(this, 69);
    // the topmost parent panel, having the theme color
    // __p_pane->SetBackgroundColour(*theme); will look into later
    __p_sizer = new wxBoxSizer(wxVERTICAL);
    // topmost parent sizer, holding everything
    __p_sizer->Add(__p_pane, 1, wxEXPAND);

    wxBoxSizer* p_sizer = new wxBoxSizer(wxHORIZONTAL);
    // parent sizer for components
    wxBoxSizer* l_sizer = new wxBoxSizer(wxVERTICAL);
    // left sizer, for cbox & lbox
    wxBoxSizer* r_sizer = new wxBoxSizer(wxVERTICAL);
    // right sizer for txtbox & btns

    p_sizer->Add(l_sizer, 0.5, wxEXPAND | wxALL, 10);
    p_sizer->Add(r_sizer, 1, wxEXPAND | wxALL, 10);

    gen_cbox = new wxComboBox(__p_pane, ID_LIST);
    {
        std::ifstream file((GEN_INDEX_N));
        add_elements(genres, file);
    }
    gen_cbox->SetSelection(0);
    l_sizer->Add(gen_cbox, 0.5, wxEXPAND | wxALL | wxALIGN_TOP, 15);

    wxBoxSizer* r_btn_sizer = new wxBoxSizer(wxHORIZONTAL);
    lastLogs = new wxButton(__p_pane, ID_BTN1, "Show Last 10 Logs");
    allLogs = new wxButton(__p_pane, ID_BTN2, "Show all saved Logs");
    r_btn_sizer->Add(lastLogs, 1, wxEXPAND | wxALL, 10);
    r_btn_sizer->Add(allLogs, 1, wxEXPAND | wxALL, 10);
    r_sizer->Add(r_btn_sizer, 0.5, wxEXPAND | wxALL | wxALIGN_TOP, 10);

    logs = new wxTextCtrl(__p_pane, 69, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE | wxTE_AUTO_URL);
    // (*logs) << "Fuck My Pussy harder" << ".\n" << "Cum in me more and more";
    {
        std::ifstream file(uFolder + FSEP + "LastLogs.baka");
        readTrackerFile(file, LogList, logs);
    }
    r_sizer->Add(logs, 2, wxEXPAND | wxALL, 5);

    // menu stuffs... ignore this sheesh
    __add__ = new wxMenu();
    __add__->Append(ID_ADDGENRE, "&Add Genre", "Add a New Genre");

    wxMenu* sett = new wxMenu();
    sett->Append(ID_SETT, "&Settings", "Settings Manager for this crap");

    wxMenu* abt = new wxMenu();
    abt->Append(wxID_ABOUT, "&About", "About me and whatever you can call it");

    wxMenu* quit = new wxMenu();
    quit->Append(wxID_EXIT, "&Quit", "Quit this Crap");

    mbar = new wxMenuBar();
    mbar->Append(__add__, "&Add");
    mbar->Append(sett, "&Settings");
    mbar->Append(abt, "&About");
    mbar->Append(quit, "&Quit");

    SetMenuBar(mbar);

    CreateStatusBar();

    __p_pane->SetSizerAndFit(p_sizer);
    this->SetSizerAndFit(__p_sizer);
}

void mainFrame::add_elements(std::string*& str, std::ifstream& file2read)
{
    gen_cbox->Clear();
    std::string pafs = "";
    unsigned int len = 0;
    {
        std::string line;
        int index = 0;
        while (getline(file2read, line)) {
            index = line.find_last_of(SEP);
            gen_cbox->Append(line.substr(0, index));
            pafs += line.substr(index + 1) + '\n';
            len++;
        }
    }

    if (len == 0)
        return;

    if (str != nullptr)
    {
        delete[] str;
    }

    str = new std::string[len];
    int index = 0;
    for (unsigned int i = 0; i < len; i++)
    {
        index = pafs.find_first_of('\n');
        str[i] = pafs.substr(0, index);
        pafs = pafs.substr(index + 1);
    }
}

inline void mainFrame::create_frame()
{
    grp_sizer = new wxBoxSizer(wxHORIZONTAL);
    // sizer for everything

    wxBoxSizer* l_sizer = new wxBoxSizer(wxVERTICAL);
    // left sizer
    wxBoxSizer* r_sizer = new wxBoxSizer(wxVERTICAL);
    // rite sizer

    grp_sizer->Add(l_sizer, 0.5, wxEXPAND | wxALL, 10);
    grp_sizer->Add(r_sizer, 1, wxEXPAND | wxALL, 10);

    // add combobox
    l_sizer->Add(gen_cbox, 0.5, wxEXPAND | wxALL | wxALIGN_TOP, 15);
    entries = new wxListBox(__p_pane, ID_E_LIST, wxDefaultPosition, wxDefaultSize, 1, nullptr);
    wxBoxSizer* btn_sizer = new wxBoxSizer(wxVERTICAL);
    wxButton* btn_add_log = new wxButton(__p_pane, ID_ADDLOG, "Add Log");
    btn_sizer->Add(btn_add_log, 1, wxEXPAND | wxALL, 10);
    r_sizer->Add(btn_sizer, 0.5, wxEXPAND | wxALL | wxALIGN_TOP, 10);

    r_sizer->Add(logs, 2, wxEXPAND | wxALL, 5);
}