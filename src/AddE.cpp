#include "AddE.h"

AddE::AddE(wxWindow* frame, const wxString& title, ReadOptions readOption, const wxString& entryName, const wxPoint& pos, const wxSize& size)
	:
	wxFrame(frame, 69, title, pos, size, wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT)
{
	__frame = frame;
	__frame->Enable(false);

	wxStaticText* name = new wxStaticText(this, 6, ("Name:    " + entryName), wxPoint(20, 5), wxDefaultSize, wxALIGN_LEFT);
	wxStaticText* det = new wxStaticText(this, 6, "Details:", wxPoint(20, 60), wxDefaultSize, wxALIGN_LEFT);
	if (readOption == Anime) {
		wxStaticText* __date = new wxStaticText(this, 6, "Date:", wxPoint(20, 30), wxDefaultSize, wxALIGN_LEFT);
	}

	details = new wxTextCtrl(this, 6969, "Details", wxPoint(20, 50 * 2), wxSize(100, 100));
	
	name = nullptr;
	det = nullptr;
}

AddE::~AddE()
{
	details = nullptr;
	__frame->Enable();
}
