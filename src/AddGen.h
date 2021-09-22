#pragma once
#include <wx/wx.h>

class AddGen :
    public wxFrame
{
public:
    AddGen(wxWindow* frame, const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    wxTextCtrl* gen_name = nullptr;

    void addGen(wxCommandEvent& evt);
    void addGenN_entry(wxCommandEvent& evt);
    void cancel(wxCommandEvent& evt);

    enum
    {
        ID_GENN,
        ID_ADD,
        ID_ADDG_N_E,
        ID_CANCEL
    };

    wxDECLARE_EVENT_TABLE();

    ~AddGen();
};