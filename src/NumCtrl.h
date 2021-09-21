#pragma once

// includes
#include <wx/wx.h>
#include <wx/textctrl.h>


class NumCtrl : public wxTextCtrl
{
public:
    NumCtrl(wxWindow* parent, wxWindowID id, const wxString& s = wxEmptyString, long style = 0L);

private:
    DECLARE_EVENT_TABLE();

    void onType(wxKeyEvent& evt);

    int GetNum(wxCommandEvent& evt);
};
