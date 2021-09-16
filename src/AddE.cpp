#include "AddE.h"

AddE::AddE(wxWindow* frame, const wxString& title, ReadOptions readOption, const wxSize& size)
	:
	wxFrame(frame, 69, title, wxDefaultPosition, size, wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT)
{
	details = new wxTextCtrl(this, 6969, wxEmptyString, wxDefaultPosition, wxDefaultSize);
}

AddE::~AddE()
{
	details = nullptr;
}
