#pragma once
#include <wx/wx.h>

class Passwd
	:public wxFrame
{
	enum {
		ID_PWD_TXT,
		ID_GO_BTN
	};

	wxTextCtrl* password = nullptr;

	const char* grp_index_paf;

public:
	Passwd(std::string title, const char* paf);

	void OnGo(wxCommandEvent& evt);

	~Passwd() {}

	wxDECLARE_EVENT_TABLE();
};

