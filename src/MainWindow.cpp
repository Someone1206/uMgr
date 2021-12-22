#include "MainWindow.h"
#include "ufw/fileIO.h"


MainWindow::MainWindow(std::string title, const wxPoint& pos, const char* _gen_paf)
	:wxFrame(nullptr, 69, title, pos), gen_paf(_gen_paf)
{
	// read the gen file
	ReadGen();
	__p_pane = new wxPanel(this);
	__p_sizer = new wxBoxSizer(wxVERTICAL);
	__p_sizer->Add(__p_pane, 1, wxEXPAND);
	p_log_s = new wxBoxSizer(wxHORIZONTAL);

	grp_list = new wxChoice(__p_pane, ID_GRP_LIST,
		wxDefaultPosition, wxDefaultSize
	);
	{
		size_t len = names.size();
		for (size_t i = 0; i < len; i++)
		{
			grp_list->Append(names[i]);
		}
	}

	wxBoxSizer* l_sizer = new wxBoxSizer(wxVERTICAL);
	grp_list->SetSelection(0);
	l_sizer->Add(grp_list, 0.5, wxEXPAND | wxALL | wxALIGN_TOP, 15);

	wxBoxSizer* r_btn_sizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* all_logs = new wxButton(__p_pane, ID_BTN_AL, "Show All Logs");
	wxButton* last_logs = new wxButton(__p_pane, ID_BTN_LL, "Show Last 10 Logs");
	r_btn_sizer->Add(last_logs, 1, wxEXPAND | wxALL, 10);
	r_btn_sizer->Add(all_logs, 1, wxEXPAND | wxALL, 10);

	logs = new wxTextCtrl(__p_pane, 69, wxEmptyString, wxDefaultPosition,
		wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE | wxTE_AUTO_URL
	);
	{
		std::ifstream file(GV::user_folder + GV::fsep + "LastLogs.baka");
		readTrackerFile(file, LogList, logs);
	}
	wxBoxSizer* r_sizer = new wxBoxSizer(wxVERTICAL);
	r_sizer->Add(r_btn_sizer, 1, wxEXPAND | wxALL | wxALIGN_TOP, 10);
	r_sizer->Add(logs, 2, wxEXPAND | wxALL, 5);

	p_log_s->Add(l_sizer, 1, wxEXPAND | wxALL, 2);
	p_log_s->Add(r_sizer, 4, wxEXPAND | wxALL, 2);

	__p_pane->SetSizerAndFit(p_log_s);
	this->SetSizerAndFit(__p_sizer);
}


void MainWindow::ReadGen() {
	// ill improve dis later
	std::ifstream file(gen_paf);
	std::string temp = "";
	int index = 0;
	while (getline(file, temp)) {
		index = temp.find_last_of((char)1);
		names.push_back(temp.substr(0, index));
		paths.push_back(temp.substr(index + 1));
	}
	file.close();
}