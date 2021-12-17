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

public:
	Passwd(std::string title);

	void OnGo(wxCommandEvent& evt);

	~Passwd() {}

	wxDECLARE_EVENT_TABLE();
};

