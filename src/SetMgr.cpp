#include "SetMgr.h"
#include "ufw/init.h"
#include "ufw/fileIO.h"

wxBEGIN_EVENT_TABLE(SetMgr, wxFrame)
    EVT_BUTTON(ID_OKAI, SetMgr::kBai)
    EVT_BUTTON(ID_APPLY, SetMgr::app)
    EVT_BUTTON(ID_CANCEL, SetMgr::canc)
    EVT_CHECKBOX(ID_CR_F, SetMgr::smth)
    EVT_CHECKBOX(ID_THEME, SetMgr::smth)
wxEND_EVENT_TABLE()

SetMgr::SetMgr(wxWindow* frame, const wxPoint& pos, const wxSize& size, wxColor* theme)
    :
    wxFrame(frame, 69, "Settings Manager", pos, size, wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT) {

    __frame = frame;
    __frame->Enable(false);

    pane = new wxPanel(this, 85);
    pane->SetBackgroundColour(*theme);

    // pmpt = new wxStaticText(pane, 99, "", wxPoint(10, 10));

    cdf = new wxCheckBox(pane, ID_CR_F, "Create Default Application folders", wxPoint(10, 20), wxDefaultSize);
    th = new wxCheckBox(pane, ID_THEME, "Dark Theme. (Needs Application Restart)", wxPoint(10, 40), wxDefaultSize);
    bool err = settings(choices);
    cdf->SetValue(choices[0]);
    th->SetValue(choices[1]);

    ps[0] = choices[0];
    ps[1] = choices[1];

    if (!err) {
        wxMessageBox(
            "Couldn't read Settings.baka file. File probably not present or corrupted or I am sh*t",
            "FU*KIN' ERROR",
            wxICON_ERROR | wxOK
        );
        int choice = wxMessageBox(
            "Reinitialize the file structure(this will create all default genres. "
            "You can delete them manually later). Yes to reinitialize and no to close"
            " Settings Manager. If that doesn't work just fu**in' ditch me.",
            "Reinitialize File Structure?",
            wxYES_NO | wxICON_QUESTION
        );

        if (choice == wxYES)
            init(choices);
        else
            Close(true);
    }



    okaiBai = new wxButton(pane, ID_OKAI, "Okay", wxPoint(size.x - 250, size.y - 70));
    cancel = new wxButton(pane, ID_CANCEL, "Cancel", wxPoint(size.x - 175, size.y - 70));
    apply = new wxButton(pane, ID_APPLY, "Apply", wxPoint(size.x - 100, size.y - 70));

    frame = nullptr;
    theme = nullptr;
}

void SetMgr::kBai(wxCommandEvent& evt) {
    writeFile(choices);
    ps[0] = choices[0];
    ps[1] = choices[1];
    Destroy();
}

void SetMgr::app(wxCommandEvent& evt) {
    writeFile(choices);
    ps[0] = choices[0];
    ps[1] = choices[1];
}

void SetMgr::canc(wxCommandEvent& evt) {
    Destroy();
}

void SetMgr::smth(wxCommandEvent& evt) {
    choices[0] = cdf->GetValue();
    choices[1] = th->GetValue();
}


SetMgr::~SetMgr() {
    if (ps[0] != choices[0] || ps[1] != choices[1]) {
        int choice = wxMessageBox(
            "You've changed your settings, wanna save em?",
            "Save Changes?",
            wxYES_NO | wxICON_QUESTION
        );
        if (choice == wxYES)
            writeFile(choices);
        else
            Destroy();
    }

    // delete[] choices;
    // delete[] ps;

    pane = nullptr;
    cdf = nullptr;
    th = nullptr;
    okaiBai = nullptr;
    apply = nullptr;
    cancel = nullptr;

    __frame->Enable(true);
}
