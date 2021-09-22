#pragma once
#include <wx/wx.h>
#include <wx/calctrl.h>
#include <wx/timectrl.h>
#include "ufw/fileIO.h"
#include "NumCtrl.h"

class AddLog :
    public wxFrame
{
public:
    AddLog(wxWindow* frame, const wxString& title, ReadOptions readOption, const wxString& entryName,
        const wxPoint& pos, const wxSize& size, const wxString& path);

private:
    ReadOptions option;
    std::string paf = "", name = "";

    wxWindow* __frame = nullptr;

    wxCalendarCtrl* date = nullptr;
    wxStaticText* __date = nullptr;

    wxTimePickerCtrl* time = nullptr;
    wxStaticText* __time = nullptr;
    wxButton* time_now = nullptr;

    NumCtrl* param1 = nullptr;      // param1 for anime -> Season, manga -> Chapter
    NumCtrl* param2 = nullptr;      // param2 for anime -> episode, manga -> page stopped on
    wxTextCtrl* details = nullptr;

    void onDateSel(wxCalendarEvent& evt);
    void onTimeSel(wxDateEvent& evt);
    void onTimeNow(wxCommandEvent& evt);
    void onDateToday(wxCommandEvent& evt);
    void limitExceed(wxCommandEvent& evt);

    void okei(wxCommandEvent& evt);
    void cancel(wxCommandEvent& evt);

    // format the date from yyyy-mm-dd to dd - "Month Name" - yyyy
    wxString formatDate(wxString string1);

    wxDECLARE_EVENT_TABLE();

    ~AddLog();
    enum {
        ID_CAL,
        ID_TIME,
        ID_TIME_NOW,
        ID_DATE_NOW,
        ID_ADD,
        ID_CANCEL,
        ID_PARAMS
    };
};
