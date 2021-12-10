#pragma once
#include "SetMgr.h"
#include "About.h"
#include "AddLog.h"

class mainFrame :
    public wxFrame
{
public:
    mainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

    wxColor* theme = nullptr;

    void add_elements(std::string*& str, std::ifstream& file2read);

private:
    bool _isLog = true, _allLog = false;
    ReadOptions fileRop = Anime;
    std::string* genres = nullptr;

    // buttons for log
    wxButton* lastLogs = nullptr;
    wxButton* allLogs = nullptr;

    // Controls that'll never change
    // wxBoxSizer* r_btn_sizer = nullptr;
    wxPanel* __p_pane = nullptr;
    wxBoxSizer* __p_sizer = nullptr;
    wxBoxSizer* grp_sizer = nullptr;
    wxTextCtrl* logs = nullptr;
    wxComboBox* gen_cbox = nullptr;

    // menu stuffs
    wxMenuBar* mbar = nullptr;
    wxMenu* __add__ = nullptr;

    //
    wxListBox* entries = nullptr;
    wxButton* addLog = nullptr;
    wxString* entryList = nullptr;
    std::string* entryFP = nullptr;
    

    inline void create_frame();


    // functions needed
    void lastLogsS(wxCommandEvent& evt);
    // when last logs is clicked
    void allLogsS(wxCommandEvent& evt);
    // when all logs is clicked
    void onAbout(wxCommandEvent& evt);
    // when about is clicked
    void onExit(wxCommandEvent& evt);
    // on exit
    void onSet(wxCommandEvent& evt);
    // when preferences is clicked

    void choice(wxCommandEvent& evt);
    // when an choice in the combobox is clicked
    void entryChoice(wxCommandEvent& evt);
    // when an entry is clicked
    void _addLog_(wxCommandEvent& evt);
    // on add log

    void genAdd(wxCommandEvent& evt);
    // on add genre/group
    void entryAdd(wxCommandEvent& evt);
    // on add entry

    wxDECLARE_EVENT_TABLE();

    enum {
        ID_BTN1,
        ID_BTN2,
        ID_SETT,
        ID_PANE,
        ID_LIST,
        ID_E_LIST,
        ID_ADDLOG,
        ID_ADDGENRE,
        ID_ADDENTRY
    };

public:
    ~mainFrame();
};
