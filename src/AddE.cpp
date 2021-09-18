#include "AddE.h"

AddE::AddE(wxWindow* frame, const wxString& title, ReadOptions readOption, const wxSize& size)
	:
	wxFrame(frame, 69, title, wxDefaultPosition, size, wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT)
{
	{
		wxStaticText det(this, 6, "Details:", wxPoint(20,10), wxDefaultSize, wxALIGN_LEFT);
	}
	details = new wxTextCtrl(this, 6969, "Details", wxPoint(20, 50), wxSize(100, 100));
}

AddE::~AddE()
{
	details = nullptr;
}
