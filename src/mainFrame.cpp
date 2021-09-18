#include "mainFrame.h"

wxBEGIN_EVENT_TABLE(mainFrame, wxFrame)
    EVT_BUTTON(ID_BTN1, mainFrame::lastLogsS)
    EVT_BUTTON(ID_BTN2, mainFrame::allLogsS)

    EVT_MENU(ID_SETT, mainFrame::onSet)
    EVT_MENU(wxID_ABOUT, mainFrame::onAbout)
    EVT_MENU(wxID_EXIT, mainFrame::onExit)

    EVT_CHOICE(ID_LIST, mainFrame::choice)
    EVT_CHOICE(ID_E_LIST, mainFrame::entryChoice)

    EVT_BUTTON(ID_ADDLOG, mainFrame::addE)
wxEND_EVENT_TABLE()

mainFrame::mainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    :
    wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    {
        bool choices[] = { 1,1 };

        init(choices);

        if (!choices[1])
            theme = new wxColor(240, 240, 240);
        else
            theme = new wxColor(30, 30, 30);
    }

    
    int len = entriesNGenres() + 1;
    genres = new wxString[len];
    genres[0] = "Log Summary";
    readTrackerFile(emptyFile, G_IndexerAndData, emptyText, 0, genres);

    list = new wxChoice(this, ID_LIST, wxPoint(10, 10), wxDefaultSize, len, genres);
    list->SetSelection(0);

    lastLogs = new wxButton(this, ID_BTN1, "&Show Last 10 Logs", wxPoint(10, 10 + 50));
    allLogs = new wxButton(this, ID_BTN2, "&Show All Logs Saved", wxPoint(10, 50 + 50));

    logs = new wxTextCtrl(this, 69, wxEmptyString, wxPoint(200, 200), wxSize(200, 250), wxTE_READONLY | wxTE_MULTILINE);
    // (*logs) << "Fuck My Pussy harder" << ".\n" << "Cum in me more and more";
    {
        ifstream file(folderN + fsep + "LastLogs.baka");
        readTrackerFile(file, LogList, logs);
    }

    // menu stuffs... ignore this sheesh
    sett = new wxMenu();
    sett->Append(ID_SETT, "&Settings", "Settings Manager for this crap");

    abt = new wxMenu();
    abt->Append(wxID_ABOUT, "&About", "About me and whatever you can call it");

    quit = new wxMenu();
    quit->Append(wxID_EXIT, "&Quit", "Quit this Crap");

    mbar = new wxMenuBar();
    mbar->Append(sett, "&Settings");
    mbar->Append(abt, "&About");
    mbar->Append(quit, "&Quit");

    SetMenuBar(mbar);

    CreateStatusBar();
}

void mainFrame::lastLogsS(wxCommandEvent& evt)
{
    if (_allLog) {
        ifstream file(folderN + fsep + "LastLogs.baka");
        readTrackerFile(file, LogList, logs);
    }
    _allLog = false;
}

void mainFrame::allLogsS(wxCommandEvent& evt) {
    if (!_allLog) {
        ifstream file(folderN + fsep + "AllLogs.hentai");
        readTrackerFile(file, LogList, logs);
    }
    _allLog = true;
}

void mainFrame::onAbout(wxCommandEvent& evt)
{
    wxPoint pos = this->GetPosition();
    about = new About(this, wxPoint(pos.x + 30, pos.y + 30), wxSize(480, 320), theme);
    about->Show();
}

void mainFrame::onExit(wxCommandEvent& evt)
{
    Close(true);
}

void mainFrame::onSet(wxCommandEvent& evt)
{
    wxPoint pos = this->GetPosition();
    this->Enable(false);
    setMgr = new SetMgr(this, wxPoint(pos.x + 30, pos.y + 30), wxSize(640, 480), theme);
    setMgr->Show();
}

void mainFrame::choice(wxCommandEvent& evt)
{
    str opt = str(genres[list->GetSelection()].mb_str());
    static str _prevOpt = str(genres[0].mb_str());

    if (opt != _prevOpt) { // if current selection != previous selection
        if (opt != str(genres[0].mb_str())) { // if != to log summary
            if (allLogs != nullptr) {
                allLogs->Destroy();
                lastLogs->Destroy();
                allLogs = nullptr;
                lastLogs = nullptr;
            }

            entryList = nullptr;
            entryFP = nullptr;

            int len = entriesNGenres((folderN + fsep + opt), true);
            // addLog = new wxButton(this, ID_ADDLOG, "&Add Log", wxPoint(10, 10 + 50 + 50), wxDefaultSize);
            
            if (addLog == nullptr)
                addLog = new wxButton(this, ID_ADDLOG, "&Add Log", wxPoint(10, 10 + 50 + 50), wxDefaultSize);
            if (len != 0) // if no entries present
            {
                entryList = new wxString[len];
                entryFP = new str[len];
                readTrackerFile(emptyFile, Entries, emptyText, 0, entryList, (folderN + fsep + opt), false, entryFP);
                if (entries == nullptr)
                    entries = new wxChoice(this, ID_E_LIST, wxPoint(10, 10 + 50), wxDefaultSize, len, entryList);
                else
                {
                    entries->SetColumns(len);
                    for (int i = 0; i < len; i++)
                    {
                        entries->SetString(i, entryList[i]);
                    }
                }
                entries->SetSelection(0);
                addLog->Enable(true);
            }
            else {
                wxString noEntries[1] = { "No Entries Made" };
                if (entries == nullptr)
                    entries = new wxChoice(this, ID_E_LIST, wxPoint(10, 10 + 50), wxDefaultSize, 1, noEntries);
                entries->SetSelection(0);
                addLog->Enable(false);
            }

            if (opt == "Anime")
                fileRop = Anime;
            else if (opt == "Manga")
                fileRop = Manga;
            else if (opt == "Movies")
                fileRop = Movies;
            else
                fileRop = Others;

            if (len != 0)
            {
                ifstream file(entryFP[0]);
                readFile(file, fileRop, logs, 0, 0, true);
            }
        }
        else {
            entries->Destroy();
            addLog->Destroy();
            entries = nullptr;
            addLog = nullptr;

            lastLogs = new wxButton(this, ID_BTN1, "&Show Last 10 Logs", wxPoint(10, 10 + 50));
            allLogs = new wxButton(this, ID_BTN2, "&Show All Logs Saved", wxPoint(10, 50 + 50));
        }
        _prevOpt = opt;
    }
}

// choice for entries
void mainFrame::entryChoice(wxCommandEvent& evt)
{
    int Eindex = entries->GetSelection();
    static int prevEindex = 0;

    if (Eindex != prevEindex) {
        ifstream file(entryFP[Eindex]);
        readFile(file, fileRop, logs, 0, 0, true);
        prevEindex = Eindex;
    }
}

// add the entry button
void mainFrame::addE(wxCommandEvent& evt)
{
    addEntry = new AddE(this, "Add New Entry", fileRop, wxSize(480, 320));
    addEntry->Show();
}

mainFrame::~mainFrame()
{
    // deleting does cause errors sometimes
    setMgr = nullptr;
    about = nullptr;

    lastLogs = nullptr;
    allLogs = nullptr;
    logs = nullptr;

    mbar = nullptr;
    sett = nullptr;
    abt = nullptr;
    quit = nullptr;

    theme = nullptr;
}
