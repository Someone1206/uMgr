#pragma once
#include <wx/wx.h>

class AddEntry
	: public wxFrame
{
public:
    AddEntry(wxWindow* parent, const wxString& title, const wxPoint& pos, const wxString& genre, bool _idk = true);

private:
    wxTextCtrl* entry_name = nullptr;
    wxString gen_name;
    bool idk = false;

    void addEntry(wxCommandEvent& evt);
    void addEntry_n_log(wxCommandEvent& evt);
    void cancel(wxCommandEvent& evt);

    enum
    {
        ID_ENTRY,
        ID_ADD,
        ID_ADDE_N_L,
        ID_CANCEL
    };

    wxDECLARE_EVENT_TABLE();

    ~AddEntry();
};

