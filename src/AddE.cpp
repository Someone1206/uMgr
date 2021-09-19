#include "AddE.h"
#include <wx/datetime.h>
#include <wx/timectrl.h>

wxBEGIN_EVENT_TABLE(AddE, wxFrame)
	EVT_CALENDAR_SEL_CHANGED(ID_CAL, onDateSel)
	EVT_TIME_CHANGED(ID_TIME, onTimeSel)
wxEND_EVENT_TABLE()

AddE::AddE(wxWindow* frame, const wxString& title, ReadOptions readOption, const wxString& entryName, const wxPoint& pos, const wxSize& size)
	:
	wxFrame(frame, 69, title, pos, size, wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT)
{
	__frame = frame;
	__frame->Enable(false);

	wxStaticText* name = new wxStaticText(this, 6, ("Name:    " + entryName), wxPoint(20, 1), wxDefaultSize, wxALIGN_LEFT);

	date = new wxCalendarCtrl(this, ID_CAL, wxDefaultDateTime, wxPoint(20, 30), wxDefaultSize,
		wxCAL_SUNDAY_FIRST | wxCAL_SHOW_HOLIDAYS | wxCAL_SHOW_SURROUNDING_WEEKS | wxCAL_SEQUENTIAL_MONTH_SELECTION | wxCAL_SHOW_WEEK_NUMBERS);
	date->SetDate(wxDateTime::Now());
	__date = new wxStaticText(this, 6, ("Date Selected:    " + formatDate(date->GetDate().FormatISODate())), wxPoint(20, 15), wxDefaultSize, wxALIGN_LEFT);

	time = new wxTimePickerCtrl(this, ID_TIME, wxDefaultDateTime, wxPoint(300, 30), wxSize(wxDefaultSize.x + 100, wxDefaultSize.y + 40));
	time->SetValue(wxDateTime::Now());
	__time = new wxStaticText(this, 6989, ("Time Selected:    " + time->GetValue().FormatISOTime()), wxPoint(300, 15), wxDefaultSize, wxALIGN_LEFT);
	// %x to replace

	wxStaticText* det = new wxStaticText(this, 6, "Details:", wxPoint(20, 250), wxDefaultSize, wxALIGN_LEFT);
	if (readOption == Anime) {
	}

	// details = new wxTextCtrl(this, 6969, "Details", wxPoint(20, 50 * 2), wxSize(100, 100));
}

void AddE::onDateSel(wxCalendarEvent& evt)
{
	__date->SetLabel(("Date Selected:    " + formatDate(evt.GetDate().FormatISODate())));
}

void AddE::onTimeSel(wxDateEvent& evt)
{
	__time->SetLabel(("Time Selected:    " + time->GetValue().FormatISOTime()));
}

wxString AddE::formatDate(wxString string1)
{
	std::string toFormat = std::string(string1.mb_str());
	int monthNo_1 = toFormat.at(4) - '0', monthNo_2 = toFormat.at(5) - '0';

	std::string month = "Jan", day = toFormat.substr(toFormat.length() - 2), year = toFormat.substr(0, 4);
	switch (monthNo_1)
	{
	case 1:
		month = "Jan";
		break;
	case 2:
		month = "Feb";
		break;
	case 3:
		month = "Mar";
		break;
	case 4:
		month = "Apr";
		break;
	case 5:
		month = "May";
		break;
	case 6:
		month = "Jun";
		break;
	case 7:
		month = "Jul";
		break;
	case 8:
		month = "Aug";
		break;
	case 9:
		month = "Sep";
		break;
	default:
		break;
	}

	switch (monthNo_2)
	{
	case 0:
		month = "Oct";
		break;
	case 1:
		month = "Nov";
		break;
	case 2:
		month = "Dec";
		break;
	default:
		break;
	}
	return wxString((day + "-" + month + "-" + year));
}

AddE::~AddE()
{
	details = nullptr;
	__frame->Enable();
}
