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

private:
    bool _isLog = true, _allLog = false;
    ReadOptions fileRop = Anime;
    wxString* genres = nullptr;

    // buttons for log
    wxButton* lastLogs = nullptr;
    wxButton* allLogs = nullptr;

    // Controls that'll never change
    wxTextCtrl* logs = nullptr;
    wxChoice* list = nullptr;

    // menu stuffs
    wxMenuBar* mbar = nullptr;
	wxMenu* __add__ = nullptr;
    wxMenu* sett = nullptr;
    wxMenu* abt = nullptr;
    wxMenu* quit = nullptr;

    //
    wxChoice* entries = nullptr;
    wxButton* addLog = nullptr;
    wxString* entryList = nullptr;
    str* entryFP = nullptr;

    // the other needed classes and windows
    SetMgr* setMgr = nullptr;
    About* about = nullptr;
    AddLog* __addLog = nullptr;

    // functions needed
    void lastLogsS(wxCommandEvent& evt);
    void allLogsS(wxCommandEvent& evt);
    void onAbout(wxCommandEvent& evt);
    void onExit(wxCommandEvent& evt);
    void onSet(wxCommandEvent& evt);

    void choice(wxCommandEvent& evt);
    void entryChoice(wxCommandEvent& evt);
    void _addLog_(wxCommandEvent& evt);

    void genAdd(wxCommandEvent& evt);
    void entryAdd(wxCommandEvent& evt);

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
