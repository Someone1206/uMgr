#include "About.h"

wxBEGIN_EVENT_TABLE(About, wxFrame)
    EVT_BUTTON(ID_OK_BTN, About::okai)
wxEND_EVENT_TABLE()

About::About(wxWindow* frame, const wxPoint& pos, const wxSize& size, wxColor* theme)
    :
    wxFrame(frame, 69, "About", pos, size) {

    win = new wxPanel(this, ID_PANEL);
    win->SetBackgroundColour(*theme);

    psizer = new wxGridSizer(2, 10, 10);

    abt = new wxStaticText(win, 6969, "Watching Hentai", wxPoint(10, 10));

    okBtn = new wxButton(win, ID_OK_BTN, "Okay", wxPoint(size.x - 100, size.y - 70));

    frame = nullptr;
    theme = nullptr;
}

void About::okai(wxCommandEvent& evt)
{
    Destroy();
}

About::~About()
{
    win = nullptr;
    abt = nullptr;
    okBtn = nullptr;
    psizer = nullptr;
}
