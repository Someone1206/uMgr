#pragma once

#include <wx/wx.h>
#include <wx/textctrl.h>


class NumCtrl : public wxTextCtrl
{
public:
    NumCtrl(wxWindow* parent, wxWindowID id, const wxString& s = wxEmptyString, long style = wxTE_CENTER);

private:
    DECLARE_EVENT_TABLE();

    void onType(wxKeyEvent& evt);
};
