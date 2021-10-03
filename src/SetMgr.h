#pragma once
#include <wx/wx.h>

class SetMgr :
    public wxFrame
{
public:
    SetMgr(wxWindow* frame, const wxPoint& pos, const wxSize& size, wxColor* theme);

private:
    bool choices[2] = { 1,1 };
    bool ps[2] = { 1,1 };

    wxWindow* __frame = nullptr;

    wxPanel* pane = nullptr;
    // wxStaticText* pmpt = nullptr;
    wxCheckBox* cdf = nullptr; // cdf = create(c) default(d) folders(f)
    wxCheckBox* th = nullptr;
    wxButton* okaiBai = nullptr;  // オカイ　バイ
    wxButton* apply = nullptr;
    wxButton* cancel = nullptr;

    void kBai(wxCommandEvent& evt);
    void app(wxCommandEvent& evt);
    void canc(wxCommandEvent& evt);

    void smth(wxCommandEvent& evt);

    wxDECLARE_EVENT_TABLE();

    enum {
        ID_CR_F,
        ID_OKAI,
        ID_APPLY,
        ID_CANCEL,
        ID_THEME
    };

public:
    ~SetMgr();

};

