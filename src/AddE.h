#pragma once
#include <wx/wx.h>
#include <wx/calctrl.h>
#include <string>
#include "ufw/fileIO.h"

class AddE :
    public wxFrame
{
public:
    AddE(wxWindow* frame, const wxString& title, ReadOptions readOption, const wxString& entryName, const wxPoint& pos, const wxSize& size);

private:
    wxWindow* __frame = nullptr;

    wxBoxSizer* _p_sizer = nullptr;

    wxCalendarCtrl* date = nullptr;
    wxStaticText* __date = nullptr;

    wxTextCtrl* time = nullptr;
    wxTextCtrl* param1 = nullptr;    // param1 for anime -> Season, manga -> Chapter, movies -> Part
    wxTextCtrl* param2 = nullptr;    // param2 for anime -> episode, manga -> page stopped on
    wxTextCtrl* details = nullptr;

    void onDateSel(wxCalendarEvent& evt);


    // format the date from yyyy-mm-dd to dd - "Month Name" - yyyy
    wxString formatDate(wxString string1);

    wxDECLARE_EVENT_TABLE();

    ~AddE();
};

enum {
    ID_CAL,
};